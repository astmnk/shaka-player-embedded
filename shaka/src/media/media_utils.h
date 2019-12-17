// Copyright 2017 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SHAKA_EMBEDDED_MEDIA_MEDIA_UTILS_H_
#define SHAKA_EMBEDDED_MEDIA_MEDIA_UTILS_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "shaka/media/media_capabilities.h"
#include "src/js/js_error.h"
#include "src/media/types.h"
#include "src/util/utils.h"

namespace shaka {
namespace media {

/** The name of the MIME parameter that contains the codecs. */
constexpr const char* kCodecMimeParam = "codecs";

/**
 * Parses a MIME type string into the type, subtype, and parameters.
 * e.g.: "video/mp4; codecs=vp9"
 *
 * @param source The MIME string to parse.
 * @param type [OUT] Where to put the type (e.g. 'video').
 * @param subtype [OUT] Where to put the subtype (e.g. 'mp4').
 * @param params [OUT] Where to put a map of parameters.
 * @returns True on success, false on parsing errors.
 */
bool ParseMimeType(const std::string& source, std::string* type,
                   std::string* subtype,
                   std::unordered_map<std::string, std::string>* params);

/** @return The container converted to the name FFmpeg expects. */
std::string NormalizeContainer(const std::string& container);

/** @return The codec converted to the name FFmpeg expects. */
std::string NormalizeCodec(const std::string& codec);

/**
 * Returns the buffered ranges that represent the regions that are buffered in
 * all of the given sources.
 *
 * Note this doesn't account for key frames, so this may not represent the
 * actual playable regions.
 */
BufferedRanges IntersectionOfBufferedRanges(
    const std::vector<BufferedRanges>& sources);

/**
 * Converts a MIME type to a MediaDecodingConfiguration that is usable with the
 * media capabilities API.
 */
MediaDecodingConfiguration ConvertMimeToDecodingConfiguration(
    const std::string& mime_type, MediaDecodingType type);

/** @return the resolution of the screen. */
std::pair<uint32_t, uint32_t> GetScreenResolution();

}  // namespace media
}  // namespace shaka

#endif  // SHAKA_EMBEDDED_MEDIA_MEDIA_UTILS_H_
