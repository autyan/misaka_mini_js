// utility.c
// Shared utility helpers for file loading and future extensions.

#include "runtime/stream.h"
#include "common/mj_error.h"
#include "common/utility.h"

// Open a file-backed stream and detect the BOM/encoding.
mj_error_t open_stream_with_encoding(const char *filename, mj_stream_t *out_stream,
                                     mj_stream_encoding_t *out_encoding, bool *out_has_bom)
{
    if (filename == NULL || out_stream == NULL || out_encoding == NULL || out_has_bom == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    mj_error_t err = mj_stream_open_file(filename, out_stream);
    if (err != MJ_OK)
    {
        return err;
    }

    err = mj_stream_detect_encoding(out_stream, out_encoding, out_has_bom);
    if (err != MJ_OK)
    {
        mj_stream_close(out_stream);
        return err;
    }

    return MJ_OK;
}
