// stream_file.c
// File-backed stream implementation.

#include "runtime/stream.h"

#include <stdio.h>

static FILE *mj_stream_as_file(mj_stream_t *stream)
{
    if (stream == NULL || stream->kind != MJ_STREAM_KIND_FILE)
    {
        return NULL;
    }
    return (FILE *)stream->ctx;
}

mj_error_t mj_stream_open_file(const char *path, mj_stream_t *out_stream)
{
    if (path == NULL || out_stream == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        return MJ_ERR_FILE_NOT_FOUND;
    }

    out_stream->kind = MJ_STREAM_KIND_FILE;
    out_stream->ctx = file;
    return MJ_OK;
}

void mj_stream_close(mj_stream_t *stream)
{
    FILE *file = mj_stream_as_file(stream);
    if (file == NULL)
    {
        return;
    }
    fclose(file);
    stream->ctx = NULL;
}

size_t mj_stream_read(mj_stream_t *stream, void *buffer, size_t size)
{
    FILE *file = mj_stream_as_file(stream);
    if (file == NULL || buffer == NULL || size == 0)
    {
        return 0;
    }
    return fread(buffer, 1, size, file);
}

int mj_stream_peek(mj_stream_t *stream, unsigned char *out_byte)
{
    FILE *file = mj_stream_as_file(stream);
    if (file == NULL || out_byte == NULL)
    {
        return -1;
    }

    int value = fgetc(file);
    if (value == EOF)
    {
        return -1;
    }

    if (ungetc(value, file) == EOF)
    {
        return -1;
    }

    *out_byte = (unsigned char)value;
    return 0;
}

int mj_stream_seek(mj_stream_t *stream, long offset, int origin)
{
    FILE *file = mj_stream_as_file(stream);
    if (file == NULL)
    {
        return -1;
    }
    return fseek(file, offset, origin);
}

long mj_stream_tell(mj_stream_t *stream)
{
    FILE *file = mj_stream_as_file(stream);
    if (file == NULL)
    {
        return -1L;
    }
    return ftell(file);
}

mj_error_t mj_stream_detect_encoding(mj_stream_t *stream, mj_stream_encoding_t *out_encoding, bool *out_has_bom)
{
    if (stream == NULL || out_encoding == NULL || out_has_bom == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    FILE *file = mj_stream_as_file(stream);
    if (file == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    fpos_t pos;
    if (fgetpos(file, &pos) != 0)
    {
        return MJ_ERR_FILE_READ;
    }

    unsigned char bom[4] = {0};
    size_t read_count = fread(bom, 1, sizeof(bom), file);

    if (fsetpos(file, &pos) != 0)
    {
        return MJ_ERR_FILE_READ;
    }

    *out_has_bom = false;
    *out_encoding = MJ_STREAM_ENCODING_UTF8;

    if (read_count >= 4)
    {
        if (bom[0] == 0x00 && bom[1] == 0x00 && bom[2] == 0xFE && bom[3] == 0xFF)
        {
            *out_encoding = MJ_STREAM_ENCODING_UTF32_BE;
            *out_has_bom = true;
            return MJ_OK;
        }
        if (bom[0] == 0xFF && bom[1] == 0xFE && bom[2] == 0x00 && bom[3] == 0x00)
        {
            *out_encoding = MJ_STREAM_ENCODING_UTF32_LE;
            *out_has_bom = true;
            return MJ_OK;
        }
    }

    if (read_count >= 3)
    {
        if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)
        {
            *out_encoding = MJ_STREAM_ENCODING_UTF8;
            *out_has_bom = true;
            return MJ_OK;
        }
    }

    if (read_count >= 2)
    {
        if (bom[0] == 0xFE && bom[1] == 0xFF)
        {
            *out_encoding = MJ_STREAM_ENCODING_UTF16_BE;
            *out_has_bom = true;
            return MJ_OK;
        }
        if (bom[0] == 0xFF && bom[1] == 0xFE)
        {
            *out_encoding = MJ_STREAM_ENCODING_UTF16_LE;
            *out_has_bom = true;
            return MJ_OK;
        }
    }

    return MJ_OK;
}
