#pragma once

#include <cbor.h>
#include <time.h>
#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "format_specification.h"
#include "dns.h"
#include "block_table.h"
#include "file_preamble.h"
#include "block.h"
#include "hash.h"
#include "interface.h"
#include "timestamp.h"
#include "writer.h"
#include "cdns_encoder.h"

namespace CDNS {

    /**
     * @brief Class serving as C-DNS library's main interface with users
     *
     * CdnsExporter is initialized with filled File preamble structure, output destination
     * and output compression option. User only needs to call buffer_*() methods, which
     * buffer records, events and malformed messages to C-DNS block and when the block is full,
     * it automatically gets written to output.
     *
     * To change the output file or file descriptor user can call rotate_output() method.
     *
     * To enforce writing of not fully buffered block to output write_block() method is provided.
     * This method can also write to output an externally created C-DNS block. (WARNING: External
     * blocks aren't checked against CdnsExporter's Block parameters. This is up to the user!!!)
     */
    class CdnsExporter {
        public:
        /**
         * @brief Construct a new CdnsExporter object to output C-DNS data
         * @param fp Filled C-DNS File preamble with file parameters
         * @param out C-DNS output to open (file name[std::string] or file descriptor[int])
         * @param compression Type of compression for the output C-DNS data
         */
        template<typename T>
        CdnsExporter(FilePreamble& fp, const T& out, CborOutputCompression compression)
            : m_file_preamble(fp), m_block(fp.get_block_parameters(0), 0), m_encoder(out, compression),
              m_active_block_parameters(0), m_blocks_written(0) {}

        /**
         * @brief Destroy the CdnsExporter object and write the end of C-DNS output
         * if any output is currently open
         */
        ~CdnsExporter() {
            if (m_blocks_written > 0)
                m_encoder.write_break();
        }

        /** Delete [move] copy constructors and assignment operators */
        CdnsExporter(CdnsExporter& copy) = delete;
        CdnsExporter(CdnsExporter&& copy) = delete;
        CdnsExporter& operator=(CdnsExporter& rhs) = delete;
        CdnsExporter& operator=(CdnsExporter&& rhs) = delete;

        /**
         * @brief Buffer new DNS record to C-DNS block
         * @param qr New DNS record to buffer
         * @throw std::exception if inserting DNS record to the Block fails
         * @return Number of uncompressed bytes written if full Block was written to output, 0 otherwise
         */
        std::size_t buffer_qr(const GenericQueryResponse& qr) {
            std::size_t written = 0;
            if (m_block.add_question_response_record(qr)) {
                written = write_block();
                return written;
            }

            return written;
        }

         /**
         * @todo
         * bool buffer_aec(generic_aec& aec);
         * bool buffer_mm(generic_mm& mm);
         */

        /**
         * @todo
         * Change Block parameters for different Blocks
         * Only when current internal Block is empty -> immediately after writing internal Block to output
         */

        /**
         * @brief Write the given C-DNS block to output
         * @param block C-DNS block to output
         * @return Number of uncompressed bytes written
         */
        std::size_t write_block(CdnsBlock& block);

        /**
         * @brief Write the internally buffered C-DNS block to output
         * @return Number of uncompressed bytes written
         */
        std::size_t write_block() {
            std::size_t written = write_block(m_block);
            m_block.clear();
            m_block.set_block_parameters(m_file_preamble.get_block_parameters(m_active_block_parameters),
                                         m_active_block_parameters);
            return written;
        }

        /**
         * @brief Close the current output and open a new one with given file name or file descriptor
         * @param out New output to open (file name[std::string] or file descriptor[int])
         * @param export_current_block If `true` currently internally buffered Block will be exported
         * before current output is closed
         * @throw CborOutputException if output rotation fails
         * @return Number of uncompressed bytes written to close current output, 0 if closing empty output
         */
        template<typename T>
        std::size_t rotate_output(const T& out, bool export_current_block) {
            std::size_t written = 0;
            if (export_current_block)
                written += write_block();

            if (m_blocks_written > 0)
                written += m_encoder.write_break();

            m_encoder.rotate_output(out);
            m_blocks_written = 0;
            return written;
        }

        /**
         * @brief Get the number of items in currently buffered Block
         * @return Number of items in currently buffered Block
         */
        std::size_t get_block_item_count() {
            return m_block.get_item_count();
        }

        /**
         * @brief Add another Block parameters to File preamble
         * @param bp New Block parameters to add
         * @return Index of the new Block parameters in File preamble array of Block parameters
         */
        index_t add_block_parameters(BlockParameters& bp) {
            return m_file_preamble.add_block_parameters(bp);
        }

        /**
         * @brief Set Block parameters used for next internally buffered CDNS blocks (doesn't
         * affect currently buffered Block)
         *
         * User can enforce using these Block parameters immediately by calling write_block() right
         * after calling this method. This writes currently buffered Block to output and starts a new
         * Block that will use these new Block parameters.
         *
         * @param index Index to File preamble's array of Block parameters
         * @return 'true' if Block parameters are successfuly set, 'false' if given index is out of
         * bounds for File preamble's array of Block parameters
         */
        bool set_active_block_parameters(index_t index) {
            if (index >= m_file_preamble.block_parameters_size())
                return false;

            m_active_block_parameters = index;
            return true;
        }

        /**
         * @brief Get index of the active Block parameters in File Preamble's array of Block parameters
         * @return Index of active Block parameters
         */
        index_t get_active_block_parameters() const {
            return m_active_block_parameters;
        }

        private:
        /**
         * @brief Writes beginning of C-DNS file (File type ID, File preamble and start of File blocks array)
         * @return Number of uncompressed bytes written
         */
        std::size_t write_file_header();

        FilePreamble m_file_preamble;
        CdnsBlock m_block;
        CdnsEncoder m_encoder;
        index_t m_active_block_parameters;

        /**
         * @brief Number of Blocks written to the currently open output (gets reset on output rotation)
         */
        std::size_t m_blocks_written;
    };
}
