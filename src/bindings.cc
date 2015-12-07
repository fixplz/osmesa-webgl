/*
 * bindings.cc
 *
 *  Created on: Dec 13, 2011
 *      Author: ngk437
 */


#include "webgl.h"
#include <cstdlib>

#define GL_PROP(name,val) target->Set(Nan::New( #name ).ToLocalChecked(), Nan::New(val))
#define GL_ALIAS(name) GL_PROP(#name, GL_ ## name)

extern "C" {
void init(Handle<Object> target)
{
  atexit(webgl::AtExit);

  Nan::SetMethod(target, "CreateContext", webgl::CreateContext);
  Nan::SetMethod(target, "DestroyContext", webgl::DestroyContext);
  Nan::SetMethod(target, "MakeCurrent", webgl::MakeCurrent);

  Nan::SetMethod(target, "uniform1f", webgl::Uniform1f);
  Nan::SetMethod(target, "uniform2f", webgl::Uniform2f);
  Nan::SetMethod(target, "uniform3f", webgl::Uniform3f);
  Nan::SetMethod(target, "uniform4f", webgl::Uniform4f);
  Nan::SetMethod(target, "uniform1i", webgl::Uniform1i);
  Nan::SetMethod(target, "uniform2i", webgl::Uniform2i);
  Nan::SetMethod(target, "uniform3i", webgl::Uniform3i);
  Nan::SetMethod(target, "uniform4i", webgl::Uniform4i);
  Nan::SetMethod(target, "uniform1fv", webgl::Uniform1fv);
  Nan::SetMethod(target, "uniform2fv", webgl::Uniform2fv);
  Nan::SetMethod(target, "uniform3fv", webgl::Uniform3fv);
  Nan::SetMethod(target, "uniform4fv", webgl::Uniform4fv);
  Nan::SetMethod(target, "uniform1iv", webgl::Uniform1iv);
  Nan::SetMethod(target, "uniform2iv", webgl::Uniform2iv);
  Nan::SetMethod(target, "uniform3iv", webgl::Uniform3iv);
  Nan::SetMethod(target, "uniform4iv", webgl::Uniform4iv);
  Nan::SetMethod(target, "pixelStorei", webgl::PixelStorei);
  Nan::SetMethod(target, "bindAttribLocation", webgl::BindAttribLocation);
  Nan::SetMethod(target, "getError", webgl::GetError);
  Nan::SetMethod(target, "drawArrays", webgl::DrawArrays);
  Nan::SetMethod(target, "uniformMatrix2fv", webgl::UniformMatrix2fv);
  Nan::SetMethod(target, "uniformMatrix3fv", webgl::UniformMatrix3fv);
  Nan::SetMethod(target, "uniformMatrix4fv", webgl::UniformMatrix4fv);

  Nan::SetMethod(target, "generateMipmap", webgl::GenerateMipmap);

  Nan::SetMethod(target, "getAttribLocation", webgl::GetAttribLocation);
  Nan::SetMethod(target, "depthFunc", webgl::DepthFunc);
  Nan::SetMethod(target, "viewport", webgl::Viewport);
  Nan::SetMethod(target, "createShader", webgl::CreateShader);
  Nan::SetMethod(target, "shaderSource", webgl::ShaderSource);
  Nan::SetMethod(target, "compileShader", webgl::CompileShader);
  Nan::SetMethod(target, "getShaderParameter", webgl::GetShaderParameter);
  Nan::SetMethod(target, "getShaderInfoLog", webgl::GetShaderInfoLog);
  Nan::SetMethod(target, "createProgram", webgl::CreateProgram);
  Nan::SetMethod(target, "attachShader", webgl::AttachShader);
  Nan::SetMethod(target, "linkProgram", webgl::LinkProgram);
  Nan::SetMethod(target, "getProgramParameter", webgl::GetProgramParameter);
  Nan::SetMethod(target, "getUniformLocation", webgl::GetUniformLocation);
  Nan::SetMethod(target, "clearColor", webgl::ClearColor);
  Nan::SetMethod(target, "clearDepth", webgl::ClearDepth);

  Nan::SetMethod(target, "disable", webgl::Disable);
  Nan::SetMethod(target, "createTexture", webgl::CreateTexture);
  Nan::SetMethod(target, "bindTexture", webgl::BindTexture);
  Nan::SetMethod(target, "texImage2D", webgl::TexImage2D);
  Nan::SetMethod(target, "texParameteri", webgl::TexParameteri);
  Nan::SetMethod(target, "texParameterf", webgl::TexParameterf);
  Nan::SetMethod(target, "clear", webgl::Clear);
  Nan::SetMethod(target, "useProgram", webgl::UseProgram);
  Nan::SetMethod(target, "createFramebuffer", webgl::CreateFramebuffer);
  Nan::SetMethod(target, "bindFramebuffer", webgl::BindFramebuffer);
  Nan::SetMethod(target, "framebufferTexture2D", webgl::FramebufferTexture2D);
  Nan::SetMethod(target, "createBuffer", webgl::CreateBuffer);
  Nan::SetMethod(target, "bindBuffer", webgl::BindBuffer);
  Nan::SetMethod(target, "bufferData", webgl::BufferData);
  Nan::SetMethod(target, "bufferSubData", webgl::BufferSubData);
  Nan::SetMethod(target, "enable", webgl::Enable);
  Nan::SetMethod(target, "blendEquation", webgl::BlendEquation);
  Nan::SetMethod(target, "blendFunc", webgl::BlendFunc);
  Nan::SetMethod(target, "enableVertexAttribArray", webgl::EnableVertexAttribArray);
  Nan::SetMethod(target, "vertexAttribPointer", webgl::VertexAttribPointer);
  Nan::SetMethod(target, "activeTexture", webgl::ActiveTexture);
  Nan::SetMethod(target, "drawElements", webgl::DrawElements);
  Nan::SetMethod(target, "flush", webgl::Flush);
  Nan::SetMethod(target, "finish", webgl::Finish);

  Nan::SetMethod(target, "vertexAttrib1f", webgl::VertexAttrib1f);
  Nan::SetMethod(target, "vertexAttrib2f", webgl::VertexAttrib2f);
  Nan::SetMethod(target, "vertexAttrib3f", webgl::VertexAttrib3f);
  Nan::SetMethod(target, "vertexAttrib4f", webgl::VertexAttrib4f);
  Nan::SetMethod(target, "vertexAttrib1fv", webgl::VertexAttrib1fv);
  Nan::SetMethod(target, "vertexAttrib2fv", webgl::VertexAttrib2fv);
  Nan::SetMethod(target, "vertexAttrib3fv", webgl::VertexAttrib3fv);
  Nan::SetMethod(target, "vertexAttrib4fv", webgl::VertexAttrib4fv);

  Nan::SetMethod(target, "blendColor", webgl::BlendColor);
  Nan::SetMethod(target, "blendEquationSeparate", webgl::BlendEquationSeparate);
  Nan::SetMethod(target, "blendFuncSeparate", webgl::BlendFuncSeparate);
  Nan::SetMethod(target, "clearStencil", webgl::ClearStencil);
  Nan::SetMethod(target, "colorMask", webgl::ColorMask);
  Nan::SetMethod(target, "copyTexImage2D", webgl::CopyTexImage2D);
  Nan::SetMethod(target, "copyTexSubImage2D", webgl::CopyTexSubImage2D);
  Nan::SetMethod(target, "cullFace", webgl::CullFace);
  Nan::SetMethod(target, "depthMask", webgl::DepthMask);
  Nan::SetMethod(target, "depthRange", webgl::DepthRange);
  Nan::SetMethod(target, "disableVertexAttribArray", webgl::DisableVertexAttribArray);
  Nan::SetMethod(target, "hint", webgl::Hint);
  Nan::SetMethod(target, "isEnabled", webgl::IsEnabled);
  Nan::SetMethod(target, "lineWidth", webgl::LineWidth);
  Nan::SetMethod(target, "polygonOffset", webgl::PolygonOffset);

  Nan::SetMethod(target, "scissor", webgl::Scissor);
  Nan::SetMethod(target, "stencilFunc", webgl::StencilFunc);
  Nan::SetMethod(target, "stencilFuncSeparate", webgl::StencilFuncSeparate);
  Nan::SetMethod(target, "stencilMask", webgl::StencilMask);
  Nan::SetMethod(target, "stencilMaskSeparate", webgl::StencilMaskSeparate);
  Nan::SetMethod(target, "stencilOp", webgl::StencilOp);
  Nan::SetMethod(target, "stencilOpSeparate", webgl::StencilOpSeparate);
  Nan::SetMethod(target, "bindRenderbuffer", webgl::BindRenderbuffer);
  Nan::SetMethod(target, "createRenderbuffer", webgl::CreateRenderbuffer);

  Nan::SetMethod(target, "deleteBuffer", webgl::DeleteBuffer);
  Nan::SetMethod(target, "deleteFramebuffer", webgl::DeleteFramebuffer);
  Nan::SetMethod(target, "deleteProgram", webgl::DeleteProgram);
  Nan::SetMethod(target, "deleteRenderbuffer", webgl::DeleteRenderbuffer);
  Nan::SetMethod(target, "deleteShader", webgl::DeleteShader);
  Nan::SetMethod(target, "deleteTexture", webgl::DeleteTexture);
  Nan::SetMethod(target, "detachShader", webgl::DetachShader);
  Nan::SetMethod(target, "framebufferRenderbuffer", webgl::FramebufferRenderbuffer);
  Nan::SetMethod(target, "getVertexAttribOffset", webgl::GetVertexAttribOffset);

  Nan::SetMethod(target, "isBuffer", webgl::IsBuffer);
  Nan::SetMethod(target, "isFramebuffer", webgl::IsFramebuffer);
  Nan::SetMethod(target, "isProgram", webgl::IsProgram);
  Nan::SetMethod(target, "isRenderbuffer", webgl::IsRenderbuffer);
  Nan::SetMethod(target, "isShader", webgl::IsShader);
  Nan::SetMethod(target, "isTexture", webgl::IsTexture);

  Nan::SetMethod(target, "renderbufferStorage", webgl::RenderbufferStorage);
  Nan::SetMethod(target, "getShaderSource", webgl::GetShaderSource);
  Nan::SetMethod(target, "validateProgram", webgl::ValidateProgram);

  Nan::SetMethod(target, "texSubImage2D", webgl::TexSubImage2D);
  Nan::SetMethod(target, "readPixels", webgl::ReadPixels);
  Nan::SetMethod(target, "getTexParameter", webgl::GetTexParameter);
  Nan::SetMethod(target, "getActiveAttrib", webgl::GetActiveAttrib);
  Nan::SetMethod(target, "getActiveUniform", webgl::GetActiveUniform);
  Nan::SetMethod(target, "getAttachedShaders", webgl::GetAttachedShaders);
  Nan::SetMethod(target, "getParameter", webgl::GetParameter);
  Nan::SetMethod(target, "getBufferParameter", webgl::GetBufferParameter);
  Nan::SetMethod(target, "getFramebufferAttachmentParameter", webgl::GetFramebufferAttachmentParameter);
  Nan::SetMethod(target, "getProgramInfoLog", webgl::GetProgramInfoLog);
  Nan::SetMethod(target, "getRenderbufferParameter", webgl::GetRenderbufferParameter);
  Nan::SetMethod(target, "getVertexAttrib", webgl::GetVertexAttrib);
  Nan::SetMethod(target, "getSupportedExtensions", webgl::GetSupportedExtensions);
  Nan::SetMethod(target, "getExtension", webgl::GetExtension);
  Nan::SetMethod(target, "checkFramebufferStatus", webgl::CheckFramebufferStatus);

  Nan::SetMethod(target, "frontFace", webgl::FrontFace);

  // OpenGL ES 2.1 constants

  /* ClearBufferMask */
  GL_ALIAS(DEPTH_BUFFER_BIT);
  GL_ALIAS(STENCIL_BUFFER_BIT);
  GL_ALIAS(COLOR_BUFFER_BIT);

  /* Boolean */
  GL_ALIAS(FALSE);
  GL_ALIAS(TRUE);

  /* BeginMode */
  GL_ALIAS(POINTS);
  GL_ALIAS(LINES);
  GL_ALIAS(LINE_LOOP);
  GL_ALIAS(LINE_STRIP);
  GL_ALIAS(TRIANGLES);
  GL_ALIAS(TRIANGLE_STRIP);
  GL_ALIAS(TRIANGLE_FAN);

  /* AlphaFunction (not supported in ES20) */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* BlendingFactorDest */
  GL_ALIAS(ZERO);
  GL_ALIAS(ONE);
  GL_ALIAS(SRC_COLOR);
  GL_ALIAS(ONE_MINUS_SRC_COLOR);
  GL_ALIAS(SRC_ALPHA);
  GL_ALIAS(ONE_MINUS_SRC_ALPHA);
  GL_ALIAS(DST_ALPHA);
  GL_ALIAS(ONE_MINUS_DST_ALPHA);

  /* BlendingFactorSrc */
  /*      GL_ZERO */
  /*      GL_ONE */
  GL_ALIAS(DST_COLOR);
  GL_ALIAS(ONE_MINUS_DST_COLOR);
  GL_ALIAS(SRC_ALPHA_SATURATE);
  /*      GL_SRC_ALPHA */
  /*      GL_ONE_MINUS_SRC_ALPHA */
  /*      GL_DST_ALPHA */
  /*      GL_ONE_MINUS_DST_ALPHA */

  /* BlendEquationSeparate */
  GL_ALIAS(FUNC_ADD);
  GL_ALIAS(BLEND_EQUATION);
  GL_ALIAS(BLEND_EQUATION_RGB);    /* same as BLEND_EQUATION */
  GL_ALIAS(BLEND_EQUATION_ALPHA);

  /* BlendSubtract */
  GL_ALIAS(FUNC_SUBTRACT);
  GL_ALIAS(FUNC_REVERSE_SUBTRACT);

  /* Separate Blend Functions */
  GL_ALIAS(BLEND_DST_RGB);
  GL_ALIAS(BLEND_SRC_RGB);
  GL_ALIAS(BLEND_DST_ALPHA);
  GL_ALIAS(BLEND_SRC_ALPHA);
  GL_ALIAS(CONSTANT_COLOR);
  GL_ALIAS(ONE_MINUS_CONSTANT_COLOR);
  GL_ALIAS(CONSTANT_ALPHA);
  GL_ALIAS(ONE_MINUS_CONSTANT_ALPHA);
  GL_ALIAS(BLEND_COLOR);

  /* Buffer Objects */
  GL_ALIAS(ARRAY_BUFFER);
  GL_ALIAS(ELEMENT_ARRAY_BUFFER);
  GL_ALIAS(ARRAY_BUFFER_BINDING);
  GL_ALIAS(ELEMENT_ARRAY_BUFFER_BINDING);

  GL_ALIAS(STREAM_DRAW);
  GL_ALIAS(STATIC_DRAW);
  GL_ALIAS(DYNAMIC_DRAW);

  GL_ALIAS(BUFFER_SIZE);
  GL_ALIAS(BUFFER_USAGE);

  GL_ALIAS(CURRENT_VERTEX_ATTRIB);

  /* CullFaceMode */
  GL_ALIAS(FRONT);
  GL_ALIAS(BACK);
  GL_ALIAS(FRONT_AND_BACK);

  /* DepthFunction */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* EnableCap */
  GL_ALIAS(TEXTURE_2D);
  GL_ALIAS(CULL_FACE);
  GL_ALIAS(BLEND);
  GL_ALIAS(DITHER);
  GL_ALIAS(STENCIL_TEST);
  GL_ALIAS(DEPTH_TEST);
  GL_ALIAS(SCISSOR_TEST);
  GL_ALIAS(POLYGON_OFFSET_FILL);
  GL_ALIAS(SAMPLE_ALPHA_TO_COVERAGE);
  GL_ALIAS(SAMPLE_COVERAGE);

  /* ErrorCode */
  GL_ALIAS(NO_ERROR);
  GL_ALIAS(INVALID_ENUM);
  GL_ALIAS(INVALID_VALUE);
  GL_ALIAS(INVALID_OPERATION);
  GL_ALIAS(OUT_OF_MEMORY);

  /* FrontFaceDirection */
  GL_ALIAS(CW);
  GL_ALIAS(CCW);

  /* GetPName */
  GL_ALIAS(LINE_WIDTH);
  GL_ALIAS(ALIASED_POINT_SIZE_RANGE);
  GL_ALIAS(ALIASED_LINE_WIDTH_RANGE);
  GL_ALIAS(CULL_FACE_MODE);
  GL_ALIAS(FRONT_FACE);
  GL_ALIAS(DEPTH_RANGE);
  GL_ALIAS(DEPTH_WRITEMASK);
  GL_ALIAS(DEPTH_CLEAR_VALUE);
  GL_ALIAS(DEPTH_FUNC);
  GL_ALIAS(STENCIL_CLEAR_VALUE);
  GL_ALIAS(STENCIL_FUNC);
  GL_ALIAS(STENCIL_FAIL);
  GL_ALIAS(STENCIL_PASS_DEPTH_FAIL);
  GL_ALIAS(STENCIL_PASS_DEPTH_PASS);
  GL_ALIAS(STENCIL_REF);
  GL_ALIAS(STENCIL_VALUE_MASK);
  GL_ALIAS(STENCIL_WRITEMASK);
  GL_ALIAS(STENCIL_BACK_FUNC);
  GL_ALIAS(STENCIL_BACK_FAIL);
  GL_ALIAS(STENCIL_BACK_PASS_DEPTH_FAIL);
  GL_ALIAS(STENCIL_BACK_PASS_DEPTH_PASS);
  GL_ALIAS(STENCIL_BACK_REF);
  GL_ALIAS(STENCIL_BACK_VALUE_MASK);
  GL_ALIAS(STENCIL_BACK_WRITEMASK);
  GL_ALIAS(VIEWPORT);
  GL_ALIAS(SCISSOR_BOX);
  /*      GL_SCISSOR_TEST */
  GL_ALIAS(COLOR_CLEAR_VALUE);
  GL_ALIAS(COLOR_WRITEMASK);
  GL_ALIAS(UNPACK_ALIGNMENT);
  GL_ALIAS(PACK_ALIGNMENT);
  GL_ALIAS(MAX_TEXTURE_SIZE);
  GL_ALIAS(MAX_VIEWPORT_DIMS);
  GL_ALIAS(SUBPIXEL_BITS);
  GL_ALIAS(RED_BITS);
  GL_ALIAS(GREEN_BITS);
  GL_ALIAS(BLUE_BITS);
  GL_ALIAS(ALPHA_BITS);
  GL_ALIAS(DEPTH_BITS);
  GL_ALIAS(STENCIL_BITS);
  GL_ALIAS(POLYGON_OFFSET_UNITS);
  /*      GL_POLYGON_OFFSET_FILL */
  GL_ALIAS(POLYGON_OFFSET_FACTOR);
  GL_ALIAS(TEXTURE_BINDING_2D);
  GL_ALIAS(SAMPLE_BUFFERS);
  GL_ALIAS(SAMPLES);
  GL_ALIAS(SAMPLE_COVERAGE_VALUE);
  GL_ALIAS(SAMPLE_COVERAGE_INVERT);

  /* GetTextureParameter */
  /*      GL_TEXTURE_MAG_FILTER */
  /*      GL_TEXTURE_MIN_FILTER */
  /*      GL_TEXTURE_WRAP_S */
  /*      GL_TEXTURE_WRAP_T */

  GL_ALIAS(NUM_COMPRESSED_TEXTURE_FORMATS);
  GL_ALIAS(COMPRESSED_TEXTURE_FORMATS);

  /* HintMode */
  GL_ALIAS(DONT_CARE);
  GL_ALIAS(FASTEST);
  GL_ALIAS(NICEST);

  /* HintTarget */
  GL_ALIAS(GENERATE_MIPMAP_HINT);

  /* DataType */
  GL_ALIAS(BYTE);
  GL_ALIAS(UNSIGNED_BYTE);
  GL_ALIAS(SHORT);
  GL_ALIAS(UNSIGNED_SHORT);
  GL_ALIAS(INT);
  GL_ALIAS(UNSIGNED_INT);
  GL_ALIAS(FLOAT);
#ifndef __APPLE__
  GL_ALIAS(FIXED);
#endif

  /* PixelFormat */
  GL_ALIAS(DEPTH_COMPONENT);
  GL_ALIAS(ALPHA);
  GL_ALIAS(RGB);
  GL_ALIAS(RGBA);
  GL_ALIAS(LUMINANCE);
  GL_ALIAS(LUMINANCE_ALPHA);

  /* PixelType */
  /*      GL_UNSIGNED_BYTE */
  GL_ALIAS(UNSIGNED_SHORT_4_4_4_4);
  GL_ALIAS(UNSIGNED_SHORT_5_5_5_1);
  GL_ALIAS(UNSIGNED_SHORT_5_6_5);

  /* Shaders */
  GL_ALIAS(FRAGMENT_SHADER);
  GL_ALIAS(VERTEX_SHADER);
  GL_ALIAS(MAX_VERTEX_ATTRIBS);
#ifndef __APPLE__
  GL_ALIAS(MAX_VERTEX_UNIFORM_VECTORS);
  GL_ALIAS(MAX_VARYING_VECTORS);
#endif
  GL_ALIAS(MAX_COMBINED_TEXTURE_IMAGE_UNITS);
  GL_ALIAS(MAX_VERTEX_TEXTURE_IMAGE_UNITS);
  GL_ALIAS(MAX_TEXTURE_IMAGE_UNITS);
#ifndef __APPLE__
  GL_ALIAS(MAX_FRAGMENT_UNIFORM_VECTORS);
#endif
  GL_ALIAS(SHADER_TYPE);
  GL_ALIAS(DELETE_STATUS);
  GL_ALIAS(LINK_STATUS);
  GL_ALIAS(VALIDATE_STATUS);
  GL_ALIAS(ATTACHED_SHADERS);
  GL_ALIAS(ACTIVE_UNIFORMS);
  GL_ALIAS(ACTIVE_UNIFORM_MAX_LENGTH);
  GL_ALIAS(ACTIVE_ATTRIBUTES);
  GL_ALIAS(ACTIVE_ATTRIBUTE_MAX_LENGTH);
  GL_ALIAS(SHADING_LANGUAGE_VERSION);
  GL_ALIAS(CURRENT_PROGRAM);

  /* StencilFunction */
  GL_ALIAS(NEVER);
  GL_ALIAS(LESS);
  GL_ALIAS(EQUAL);
  GL_ALIAS(LEQUAL);
  GL_ALIAS(GREATER);
  GL_ALIAS(NOTEQUAL);
  GL_ALIAS(GEQUAL);
  GL_ALIAS(ALWAYS);

  /* StencilOp */
  /*      GL_ZERO */
  GL_ALIAS(KEEP);
  GL_ALIAS(REPLACE);
  GL_ALIAS(INCR);
  GL_ALIAS(DECR);
  GL_ALIAS(INVERT);
  GL_ALIAS(INCR_WRAP);
  GL_ALIAS(DECR_WRAP);

  /* StringName */
  GL_ALIAS(VENDOR);
  GL_ALIAS(RENDERER);
  GL_ALIAS(VERSION);
  GL_ALIAS(EXTENSIONS);

  /* TextureMagFilter */
  GL_ALIAS(NEAREST);
  GL_ALIAS(LINEAR);

  /* TextureMinFilter */
  /*      GL_NEAREST */
  /*      GL_LINEAR */
  GL_ALIAS(NEAREST_MIPMAP_NEAREST);
  GL_ALIAS(LINEAR_MIPMAP_NEAREST);
  GL_ALIAS(NEAREST_MIPMAP_LINEAR);
  GL_ALIAS(LINEAR_MIPMAP_LINEAR);

  /* TextureParameterName */
  GL_ALIAS(TEXTURE_MAG_FILTER);
  GL_ALIAS(TEXTURE_MIN_FILTER);
  GL_ALIAS(TEXTURE_WRAP_S);
  GL_ALIAS(TEXTURE_WRAP_T);

  /* TextureTarget */
  /*      GL_TEXTURE_2D */
  GL_ALIAS(TEXTURE);

  GL_ALIAS(TEXTURE_CUBE_MAP);
  GL_ALIAS(TEXTURE_BINDING_CUBE_MAP);
  GL_ALIAS(TEXTURE_CUBE_MAP_POSITIVE_X);
  GL_ALIAS(TEXTURE_CUBE_MAP_NEGATIVE_X);
  GL_ALIAS(TEXTURE_CUBE_MAP_POSITIVE_Y);
  GL_ALIAS(TEXTURE_CUBE_MAP_NEGATIVE_Y);
  GL_ALIAS(TEXTURE_CUBE_MAP_POSITIVE_Z);
  GL_ALIAS(TEXTURE_CUBE_MAP_NEGATIVE_Z);
  GL_ALIAS(MAX_CUBE_MAP_TEXTURE_SIZE);

  /* TextureUnit */
  GL_ALIAS(TEXTURE0);
  GL_ALIAS(TEXTURE1);
  GL_ALIAS(TEXTURE2);
  GL_ALIAS(TEXTURE3);
  GL_ALIAS(TEXTURE4);
  GL_ALIAS(TEXTURE5);
  GL_ALIAS(TEXTURE6);
  GL_ALIAS(TEXTURE7);
  GL_ALIAS(TEXTURE8);
  GL_ALIAS(TEXTURE9);
  GL_ALIAS(TEXTURE10);
  GL_ALIAS(TEXTURE11);
  GL_ALIAS(TEXTURE12);
  GL_ALIAS(TEXTURE13);
  GL_ALIAS(TEXTURE14);
  GL_ALIAS(TEXTURE15);
  GL_ALIAS(TEXTURE16);
  GL_ALIAS(TEXTURE17);
  GL_ALIAS(TEXTURE18);
  GL_ALIAS(TEXTURE19);
  GL_ALIAS(TEXTURE20);
  GL_ALIAS(TEXTURE21);
  GL_ALIAS(TEXTURE22);
  GL_ALIAS(TEXTURE23);
  GL_ALIAS(TEXTURE24);
  GL_ALIAS(TEXTURE25);
  GL_ALIAS(TEXTURE26);
  GL_ALIAS(TEXTURE27);
  GL_ALIAS(TEXTURE28);
  GL_ALIAS(TEXTURE29);
  GL_ALIAS(TEXTURE30);
  GL_ALIAS(TEXTURE31);
  GL_ALIAS(ACTIVE_TEXTURE);

  /* TextureWrapMode */
  GL_ALIAS(REPEAT);
  GL_ALIAS(CLAMP_TO_EDGE);
  GL_ALIAS(MIRRORED_REPEAT);

  /* Uniform Types */
  GL_ALIAS(FLOAT_VEC2);
  GL_ALIAS(FLOAT_VEC3);
  GL_ALIAS(FLOAT_VEC4);
  GL_ALIAS(INT_VEC2);
  GL_ALIAS(INT_VEC3);
  GL_ALIAS(INT_VEC4);
  GL_ALIAS(BOOL);
  GL_ALIAS(BOOL_VEC2);
  GL_ALIAS(BOOL_VEC3);
  GL_ALIAS(BOOL_VEC4);
  GL_ALIAS(FLOAT_MAT2);
  GL_ALIAS(FLOAT_MAT3);
  GL_ALIAS(FLOAT_MAT4);
  GL_ALIAS(SAMPLER_2D);
  GL_ALIAS(SAMPLER_CUBE);

  /* Vertex Arrays */
  GL_ALIAS(VERTEX_ATTRIB_ARRAY_ENABLED);
  GL_ALIAS(VERTEX_ATTRIB_ARRAY_SIZE);
  GL_ALIAS(VERTEX_ATTRIB_ARRAY_STRIDE);
  GL_ALIAS(VERTEX_ATTRIB_ARRAY_TYPE);
  GL_ALIAS(VERTEX_ATTRIB_ARRAY_NORMALIZED);
  GL_ALIAS(VERTEX_ATTRIB_ARRAY_POINTER);
  GL_ALIAS(VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);

  /* Read Format */
#ifndef __APPLE__
  GL_ALIAS(IMPLEMENTATION_COLOR_READ_TYPE);
  GL_ALIAS(IMPLEMENTATION_COLOR_READ_FORMAT);
#endif

  /* Shader Source */
  GL_ALIAS(COMPILE_STATUS);
  GL_ALIAS(INFO_LOG_LENGTH);
  GL_ALIAS(SHADER_SOURCE_LENGTH);
#ifndef __APPLE__
  GL_ALIAS(SHADER_COMPILER);
#endif

  /* Shader Binary */
#ifndef __APPLE__
  GL_ALIAS(SHADER_BINARY_FORMATS);
  GL_ALIAS(NUM_SHADER_BINARY_FORMATS);
#endif

  /* Shader Precision-Specified Types */
#ifndef __APPLE__
  GL_ALIAS(LOW_FLOAT);
  GL_ALIAS(MEDIUM_FLOAT);
  GL_ALIAS(HIGH_FLOAT);
  GL_ALIAS(LOW_INT);
  GL_ALIAS(MEDIUM_INT);
  GL_ALIAS(HIGH_INT);
#endif

  /* Framebuffer Object. */
  GL_ALIAS(FRAMEBUFFER);
  GL_ALIAS(RENDERBUFFER);

  GL_ALIAS(RGBA4);
  GL_ALIAS(RGB5_A1);
#ifndef __APPLE__
  //GL_ALIAS(RGB565);
#endif
  GL_ALIAS(DEPTH_COMPONENT16);
  GL_ALIAS(STENCIL_INDEX);
  GL_ALIAS(STENCIL_INDEX8);
  GL_ALIAS(DEPTH_STENCIL);
  GL_ALIAS(DEPTH24_STENCIL8);

  GL_ALIAS(RENDERBUFFER_WIDTH);
  GL_ALIAS(RENDERBUFFER_HEIGHT);
  GL_ALIAS(RENDERBUFFER_INTERNAL_FORMAT);
  GL_ALIAS(RENDERBUFFER_RED_SIZE);
  GL_ALIAS(RENDERBUFFER_GREEN_SIZE);
  GL_ALIAS(RENDERBUFFER_BLUE_SIZE);
  GL_ALIAS(RENDERBUFFER_ALPHA_SIZE);
  GL_ALIAS(RENDERBUFFER_DEPTH_SIZE);
  GL_ALIAS(RENDERBUFFER_STENCIL_SIZE);

  GL_ALIAS(FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
  GL_ALIAS(FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
  GL_ALIAS(FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
  GL_ALIAS(FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);

  GL_ALIAS(COLOR_ATTACHMENT0);
  GL_ALIAS(DEPTH_ATTACHMENT);
  GL_ALIAS(STENCIL_ATTACHMENT);
  GL_ALIAS(DEPTH_STENCIL_ATTACHMENT);

  GL_ALIAS(NONE);

  GL_ALIAS(FRAMEBUFFER_COMPLETE);
  GL_ALIAS(FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
  GL_ALIAS(FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
#ifndef __APPLE__
  //GL_ALIAS(FRAMEBUFFER_INCOMPLETE_DIMENSIONS);
#endif
  GL_ALIAS(FRAMEBUFFER_UNSUPPORTED);

  GL_ALIAS(FRAMEBUFFER_BINDING);
  GL_ALIAS(RENDERBUFFER_BINDING);
  GL_ALIAS(MAX_RENDERBUFFER_SIZE);

  GL_ALIAS(INVALID_FRAMEBUFFER_OPERATION);

  /* WebGL-specific enums */
  GL_PROP("UNPACK_FLIP_Y_WEBGL", 0x9240);
  GL_PROP("UNPACK_PREMULTIPLY_ALPHA_WEBGL", 0x9241);
  GL_PROP("CONTEXT_LOST_WEBGL", 0x9242);
  GL_PROP("UNPACK_COLORSPACE_CONVERSION_WEBGL", 0x9243);
  GL_PROP("BROWSER_DEFAULT_WEBGL", 0x9244);

  //////////////////////////////
  // NOT in WebGL spec
  //////////////////////////////

  // PBO
  GL_PROP("PIXEL_PACK_BUFFER", 0x88EB);
  GL_PROP("PIXEL_UNPACK_BUFFER", 0x88EC);
  GL_PROP("PIXEL_PACK_BUFFER_BINDING", 0x88ED);
  GL_PROP("PIXEL_UNPACK_BUFFER_BINDING", 0x88EF);
}

NODE_MODULE(webgl, init)
} // extern "C"
