/**************************************************************************/
/*  openxr_meta_spatial_entity_mesh_extension_wrapper.h                   */
/**************************************************************************/
/*                       This file is part of:                            */
/*                              GODOT XR                                  */
/*                      https://godotengine.org                           */
/**************************************************************************/
/* Copyright (c) 2022-present Godot XR contributors (see CONTRIBUTORS.md) */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#pragma once

#include <openxr/openxr.h>
#include <godot_cpp/classes/open_xr_extension_wrapper_extension.hpp>
#include <godot_cpp/templates/hash_map.hpp>

#include "util.h"

using namespace godot;

// Wrapper for the XR_META_spatial_entity_mesh extension.
class OpenXRMetaSpatialEntityMeshExtensionWrapper : public OpenXRExtensionWrapperExtension {
	GDCLASS(OpenXRMetaSpatialEntityMeshExtensionWrapper, OpenXRExtensionWrapperExtension);

public:
	Dictionary _get_requested_extensions() override;

	void _on_instance_created(uint64_t instance) override;
	void _on_instance_destroyed() override;

	bool is_spatial_entity_mesh_supported() {
		return meta_spatial_entity_mesh_ext;
	}

	struct TriangleMesh {
		Vector<XrVector3f> vertices;
		Vector<uint32_t> indices;
	};

	bool get_triangle_mesh(const XrSpace &p_space, TriangleMesh &r_triangle_mesh);

	static OpenXRMetaSpatialEntityMeshExtensionWrapper *get_singleton();

	OpenXRMetaSpatialEntityMeshExtensionWrapper();
	~OpenXRMetaSpatialEntityMeshExtensionWrapper();

protected:
	static void _bind_methods();

private:
	EXT_PROTO_XRRESULT_FUNC3(xrGetSpaceTriangleMeshMETA,
			(XrSpace), space,
			(const XrSpaceTriangleMeshGetInfoMETA *), getInfo,
			(XrSpaceTriangleMeshMETA *), triangleMeshOutput)

	bool initialize_meta_spatial_entity_mesh_extension(const XrInstance &instance);

	HashMap<String, bool *> request_extensions;

	void cleanup();

	static OpenXRMetaSpatialEntityMeshExtensionWrapper *singleton;

	bool meta_spatial_entity_mesh_ext = false;
};
