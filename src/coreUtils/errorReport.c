// errorReport.c
// 
// -------------------------------------------------
// Copyright 2015-2024 Dominic Ford
//
// This file is part of EphemerisCompute.
//
// EphemerisCompute is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EphemerisCompute is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with EphemerisCompute.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "asciiDouble.h"
#include "strConstants.h"

#include "errorReport.h"

// Buffers used for preparing logging messages. Note that this is not at all thread-safe.
static char temp_stringA[LSTR_LENGTH], temp_stringB[LSTR_LENGTH], temp_stringC[LSTR_LENGTH], temp_stringD[LSTR_LENGTH], temp_stringE[LSTR_LENGTH];
char temp_err_string[FNAME_LENGTH];

//! ephem_error - Output an error log message to stderr
//! \param [in] msg - Message to output
void ephem_error(char *msg) {
    if ((msg != temp_stringA) && (msg != temp_stringB)) {
        strcpy(temp_stringA, msg);
        msg = temp_stringA;
    }
    if (DEBUG) {
        snprintf(temp_stringC, FNAME_LENGTH, "%s%s", "Error: ", msg);
        ephem_log(temp_stringC);
    }
    snprintf(temp_stringC, FNAME_LENGTH, "Error: %s\n", msg);
    fputs(temp_stringC, stderr);
}

//! ephem_fatal - Output a fatal error message to stderr, and terminate the process
//! \param [in] file - The source code file generating the fatal error
//! \param [in] line - The source code line number generating the fatal error
//! \param [in] msg - The error message to emit on stderr
void ephem_fatal(char *file, int line, char *msg) {
    char intro_line[FNAME_LENGTH];
    if (msg != temp_stringE) strcpy(temp_stringE, msg);
    snprintf(intro_line, FNAME_LENGTH, "Fatal error encountered in %s at line %d:", file, line);
    ephem_error(intro_line);
    ephem_error(temp_stringE);
    if (DEBUG) ephem_log("Terminating with error condition 1.");
    exit(1);
}

//! ephem_warning - Emit a warning message to stderr
//! \param [in] msg - Message to output
void ephem_warning(char *msg) {
    if (msg != temp_stringA) strcpy(temp_stringA, msg);
    if (DEBUG) {
        snprintf(temp_stringC, FNAME_LENGTH, "%s%s", "Warning: ", temp_stringA);
        ephem_log(temp_stringC);
    }
    snprintf(temp_stringC, FNAME_LENGTH, "Warning: %s\n", temp_stringA);
    fputs(temp_stringC, stderr);
}

//! ephem_report - Output a report-level log message to stdout
//! \param [in] msg  - Message to output
void ephem_report(char *msg) {
    if (msg != temp_stringA) strcpy(temp_stringA, msg);
    if (DEBUG) {
        snprintf(temp_stringC, FNAME_LENGTH, "%s%s", "Reporting: ", temp_stringA);
        ephem_log(temp_stringC);
    }
    snprintf(temp_stringC, FNAME_LENGTH, "%s\n", temp_stringA);
    fputs(temp_stringC, stdout);
}

//! ephem_log - Output a log-level message to <makeephem.log> in the current working directory
//! \param [in] msg  - Message to output
void ephem_log(char *msg) {
  printf("[%s] %s\n", friendly_time_string(), msg);
}

//! dcf_fread - Read some bytes from a binary file, and exit with a fatal error if they are not read
//! \param [out] ptr - A pointer to the workspace to read the bytes into
//! \param [in] size - The size of each data structure we are to read
//! \param [in] n_requested - The number of data structures to read
//! \param [in] stream - The FILE stream to read data from
//! \param [in] filename - The filename of the stream we are reading (used to produce helpful error messages)
//! \param [in] source_file - The source code file requesting this read (used to produce helpful error messages)
//! \param [in] source_line - The source code line number requesting this read (used to produce helpful error messages)
void dcf_fread(void *ptr, size_t size, size_t n_requested, FILE *stream,
               const char *input_filename, const char *source_file, const int source_line) {
    const size_t items_read = fread(ptr, size, n_requested, stream);
    if (items_read != n_requested) {
        char buffer[LSTR_LENGTH];

        const int file_end = feof(stream);
        const int file_error = ferror(stream);
        const long file_position = ftell(stream);

        fseek(stream, 0L, SEEK_END);
        const long file_end_position = ftell(stream);

        snprintf(buffer, LSTR_LENGTH, "\
Failure while trying to read file <%s>\n\
Requested read of %ld records of size %ld; only received %ld records\n\
Error code %d. EOF flag %d. File position %ld/%ld.\n\
Read was requested by <%s:%d>\n\
", input_filename, n_requested, size, items_read, file_error, file_end, file_position, file_end_position,
                 source_file, source_line);
        ephem_fatal(__FILE__, __LINE__, buffer);
        exit(1);
    }
}
