// utility.h
// Shared helpers that do not belong to a specific subsystem.

#ifndef UTILITY_H
#define UTILITY_H

#include "common/mj_error.h"
#include "runtime/stream.h"

// Open a file stream and detect BOM/encoding.
mj_error_t open_stream_with_encoding(const char *filename, mj_stream_t *out_stream,
                                     mj_stream_encoding_t *out_encoding, bool *out_has_bom);

#endif
