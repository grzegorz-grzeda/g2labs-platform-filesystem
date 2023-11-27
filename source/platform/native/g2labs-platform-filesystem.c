/*
 * MIT License
 *
 * Copyright (c) 2023 G2Labs Grzegorz Grzęda
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "g2labs-platform-filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FULL_FILE_NAME_PATH (100)

typedef char file_name_path[FULL_FILE_NAME_PATH];

void platform_filesystem_initialize(void) {}

static void construct_full_path_from_file_name(file_name_path full_path, const char* file_name) {
    strcpy(full_path, "/var/tmp/g2labs-firmware-platform-");
    strcat(full_path, file_name);
    strcat(full_path, ".txt");
}

size_t platform_filesystem_get_size_of_file(const char* file_name) {
    file_name_path file_path;
    construct_full_path_from_file_name(file_path, file_name);
    FILE* fp = fopen(file_path, "r");
    if (!fp) {
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fclose(fp);
    return size;
}

size_t platform_filesystem_store_file(const char* file_name, const void* data, size_t data_size) {
    file_name_path file_path;
    construct_full_path_from_file_name(file_path, file_name);
    FILE* fp = fopen(file_path, "w");
    if (!fp) {
        return 0;
    }
    fseek(fp, 0, SEEK_SET);
    size_t size = fwrite(data, sizeof(char), data_size, fp);
    fclose(fp);
    return size;
}

size_t platform_filesystem_load_file(const char* file_name, void* data, size_t max_data_size) {
    file_name_path file_path;
    construct_full_path_from_file_name(file_path, file_name);
    FILE* fp = fopen(file_path, "r");
    if (!fp) {
        return 0;
    }
    fseek(fp, 0, SEEK_SET);
    size_t size = fread(data, sizeof(char), max_data_size, fp);
    fclose(fp);
    return size;
}