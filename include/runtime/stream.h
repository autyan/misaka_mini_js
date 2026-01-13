// stream.h
// Streaming interface for runtime source loading.

#ifndef MINIJS_STREAM_H
#define MINIJS_STREAM_H

#include <stdbool.h>
#include <stddef.h>

#include "common/mj_error.h"

typedef enum {
    MJ_STREAM_KIND_FILE = 0
} mj_stream_kind_t;

typedef enum {
    MJ_STREAM_ENCODING_UNKNOWN = 0,
    MJ_STREAM_ENCODING_UTF8,
    MJ_STREAM_ENCODING_UTF16_LE,
    MJ_STREAM_ENCODING_UTF16_BE,
    MJ_STREAM_ENCODING_UTF32_LE,
    MJ_STREAM_ENCODING_UTF32_BE
} mj_stream_encoding_t;

typedef struct {
    mj_stream_kind_t kind;
    void *ctx;
} mj_stream_t;

// Open a file-backed stream for reading.
mj_error_t mj_stream_open_file(const char *path, mj_stream_t *out_stream);

// Close a previously opened stream.
void mj_stream_close(mj_stream_t *stream);

// Read bytes from the stream into a buffer.
size_t mj_stream_read(mj_stream_t *stream, void *buffer, size_t size);

// Peek a single byte without consuming it.
int mj_stream_peek(mj_stream_t *stream, unsigned char *out_byte);

// Seek within the stream.
int mj_stream_seek(mj_stream_t *stream, long offset, int origin);

// Tell current position in the stream.
long mj_stream_tell(mj_stream_t *stream);

// Detect BOM/encoding without consuming bytes.
mj_error_t mj_stream_detect_encoding(mj_stream_t *stream, mj_stream_encoding_t *out_encoding, bool *out_has_bom);

#endif
