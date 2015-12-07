#include <cstring>
#include <vector>
#include <iostream>

#include "webgl.h"
#include <node.h>
#include <node_buffer.h>

#ifdef _WIN32
  #define  strcasestr(s, t) strstr(strupr(s), t)
#endif

namespace webgl {

using namespace node;
using namespace v8;
using namespace std;

// forward declarations
enum GLObjectType {
  GLOBJECT_TYPE_BUFFER,
  GLOBJECT_TYPE_FRAMEBUFFER,
  GLOBJECT_TYPE_PROGRAM,
  GLOBJECT_TYPE_RENDERBUFFER,
  GLOBJECT_TYPE_SHADER,
  GLOBJECT_TYPE_TEXTURE,
};

void registerGLObj(GLObjectType type, GLuint obj);
void unregisterGLObj(GLuint obj);

// A 32-bit and 64-bit compatible way of converting a pointer to a GLuint.
static GLuint ToGLuint(const void* ptr) {
  return static_cast<GLuint>(reinterpret_cast<size_t>(ptr));
}

inline void *getImageData(Local<Value> arg) {
  return *Nan::TypedArrayContents<char>(arg);
}

template<typename Type>
inline Type* getArrayData(Local<Value> arg, int* num = NULL) {
  Nan::TypedArrayContents<Type> cont(arg);
  *num = cont.length();
  return *cont;
}

OSMesaContext getOSMesaContext(const v8::Local<v8::Value>& value) {
  if (!value->IsObject() && value->ToObject()->InternalFieldCount() < 1) {
    Nan::ThrowError("Expected context object");
    return 0;
  }

  OSMesaContext context = (OSMesaContext)Nan::GetInternalFieldPointer(value->ToObject(), 0);

  return context;
}

NAN_METHOD(CreateContext) {
  OSMesaContext context = OSMesaCreateContextExt(OSMESA_RGBA, 32, 0, 0, NULL);

  v8::Handle<v8::ObjectTemplate> obj_tmpl = v8::ObjectTemplate::New();
  obj_tmpl->SetInternalFieldCount(1);

  v8::Handle<v8::Object> obj = obj_tmpl->NewInstance();
  Nan::SetInternalFieldPointer(obj, 0, context);

  info.GetReturnValue().Set(obj);
}

NAN_METHOD(DestroyContext) {
  OSMesaContext context = getOSMesaContext(info[0]);
  if (context) OSMesaDestroyContext(context);
}

NAN_METHOD(MakeCurrent) {
  OSMesaContext context = getOSMesaContext(info[0]);
  if (!context) return;

  Nan::TypedArrayContents<char> cont(info[1]);
  int bufferSize = cont.length();
  char* buffer = *cont;

  GLsizei width = info[2]->Int32Value();
  GLsizei height = info[3]->Int32Value();

  if (width < 1 || height < 1) {
    Nan::ThrowError(Nan::New("Invalid dimensions").ToLocalChecked());
  }

  if (bufferSize < width*height*4) {
    Nan::ThrowError(Nan::New("Buffer too small").ToLocalChecked());
  }

  OSMesaMakeCurrent(context, &buffer[0], GL_UNSIGNED_BYTE, width, height);
}

NAN_METHOD(Uniform1f) {
  int location = info[0]->Int32Value();
  float x = (float) info[1]->NumberValue();

  glUniform1f(location, x);
}

NAN_METHOD(Uniform2f) {
  int location = info[0]->Int32Value();
  float x = (float) info[1]->NumberValue();
  float y = (float) info[2]->NumberValue();

  glUniform2f(location, x, y);
}

NAN_METHOD(Uniform3f) {
  int location = info[0]->Int32Value();
  float x = (float) info[1]->NumberValue();
  float y = (float) info[2]->NumberValue();
  float z = (float) info[3]->NumberValue();

  glUniform3f(location, x, y, z);
}

NAN_METHOD(Uniform4f) {
  int location = info[0]->Int32Value();
  float x = (float) info[1]->NumberValue();
  float y = (float) info[2]->NumberValue();
  float z = (float) info[3]->NumberValue();
  float w = (float) info[4]->NumberValue();

  glUniform4f(location, x, y, z, w);
}

NAN_METHOD(Uniform1i) {
  int location = info[0]->Int32Value();
  int x = info[1]->Int32Value();

  glUniform1i(location, x);
}

NAN_METHOD(Uniform2i) {
  int location = info[0]->Int32Value();
  int x = info[1]->Int32Value();
  int y = info[2]->Int32Value();

  glUniform2i(location, x, y);
}

NAN_METHOD(Uniform3i) {
  int location = info[0]->Int32Value();
  int x = info[1]->Int32Value();
  int y = info[2]->Int32Value();
  int z = info[3]->Int32Value();

  glUniform3i(location, x, y, z);
}

NAN_METHOD(Uniform4i) {
  int location = info[0]->Int32Value();
  int x = info[1]->Int32Value();
  int y = info[2]->Int32Value();
  int z = info[3]->Int32Value();
  int w = info[4]->Int32Value();

  glUniform4i(location, x, y, z, w);
}

NAN_METHOD(Uniform1fv) {
  int location = info[0]->Int32Value();
  int num=0;
  GLfloat *ptr=getArrayData<GLfloat>(info[1],&num);
  glUniform1fv(location, num, ptr);
}

NAN_METHOD(Uniform2fv) {
  int location = info[0]->Int32Value();
  int num=0;
  GLfloat *ptr=getArrayData<GLfloat>(info[1],&num);
  num /= 2;
  glUniform2fv(location, num, ptr);
}

NAN_METHOD(Uniform3fv) {
  int location = info[0]->Int32Value();
  int num=0;
  GLfloat *ptr=getArrayData<GLfloat>(info[1],&num);
  num /= 3;

  glUniform3fv(location, num, ptr);
}

NAN_METHOD(Uniform4fv) {
  int location = info[0]->Int32Value();
  int num=0;
  GLfloat *ptr=getArrayData<GLfloat>(info[1],&num);
  num /= 4;

  glUniform4fv(location, num, ptr);
}

NAN_METHOD(Uniform1iv) {
  int location = info[0]->Int32Value();
  int num=0;
  GLint *ptr=getArrayData<GLint>(info[1],&num);

  glUniform1iv(location, num, ptr);
}

NAN_METHOD(Uniform2iv) {
  int location = info[0]->Int32Value();
  int num=0;
  GLint *ptr=getArrayData<GLint>(info[1],&num);
  num /= 2;

  glUniform2iv(location, num, ptr);
}

NAN_METHOD(Uniform3iv) {
  int location = info[0]->Int32Value();
  int num=0;
  GLint *ptr=getArrayData<GLint>(info[1],&num);
  num /= 3;
  glUniform3iv(location, num, ptr);
}

NAN_METHOD(Uniform4iv) {
  int location = info[0]->Int32Value();
  int num=0;
  GLint *ptr=getArrayData<GLint>(info[1],&num);
  num /= 4;
  glUniform4iv(location, num, ptr);
}

NAN_METHOD(PixelStorei) {
  int pname = info[0]->Int32Value();
  int param = info[1]->Int32Value();

  glPixelStorei(pname,param);
}

NAN_METHOD(BindAttribLocation) {
  int program = info[0]->Int32Value();
  int index = info[1]->Int32Value();
  String::Utf8Value name(info[2]);

  glBindAttribLocation(program, index, *name);
}


NAN_METHOD(GetError) {
  return info.GetReturnValue().Set(Nan::New(glGetError()));
}


NAN_METHOD(DrawArrays) {
  int mode = info[0]->Int32Value();
  int first = info[1]->Int32Value();
  int count = info[2]->Int32Value();

  glDrawArrays(mode, first, count);
}

NAN_METHOD(UniformMatrix2fv) {
  GLint location = info[0]->Int32Value();
  GLboolean transpose = info[1]->BooleanValue();

  GLsizei count=0;
  GLfloat* data=getArrayData<GLfloat>(info[2],&count);

  if (count < 4) {
    Nan::ThrowError("Not enough data for UniformMatrix2fv");
  }

  glUniformMatrix2fv(location, count / 4, transpose, data);
}

NAN_METHOD(UniformMatrix3fv) {
  GLint location = info[0]->Int32Value();
  GLboolean transpose = info[1]->BooleanValue();
  GLsizei count=0;
  GLfloat* data=getArrayData<GLfloat>(info[2],&count);

  if (count < 9) {
    Nan::ThrowError("Not enough data for UniformMatrix3fv");
  }

  glUniformMatrix3fv(location, count / 9, transpose, data);
}

NAN_METHOD(UniformMatrix4fv) {
  GLint location = info[0]->Int32Value();
  GLboolean transpose = info[1]->BooleanValue();
  GLsizei count=0;
  GLfloat* data=getArrayData<GLfloat>(info[2],&count);

  if (count < 16) {
    Nan::ThrowError("Not enough data for UniformMatrix4fv");
  }

  glUniformMatrix4fv(location, count / 16, transpose, data);
}

NAN_METHOD(GenerateMipmap) {
  GLint target = info[0]->Int32Value();
  glGenerateMipmap(target);
}

NAN_METHOD(GetAttribLocation) {
  int program = info[0]->Int32Value();
  String::Utf8Value name(info[1]);

  return info.GetReturnValue().Set(Nan::New(glGetAttribLocation(program, *name)));
}


NAN_METHOD(DepthFunc) {
  glDepthFunc(info[0]->Int32Value());
}


NAN_METHOD(Viewport) {
  int x = info[0]->Int32Value();
  int y = info[1]->Int32Value();
  int width = info[2]->Int32Value();
  int height = info[3]->Int32Value();

  glViewport(x, y, width, height);
}

NAN_METHOD(CreateShader) {
  GLuint shader=glCreateShader(info[0]->Int32Value());
  #ifdef LOGGING
  cout<<"createShader "<<shader<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_SHADER, shader);
  return info.GetReturnValue().Set(Nan::New(shader));
}


NAN_METHOD(ShaderSource) {
  int id = info[0]->Int32Value();
  String::Utf8Value code(info[1]);

  const char* codes[1];
  codes[0] = *code;
  GLint length=code.length();

  glShaderSource  (id, 1, codes, &length);
}


NAN_METHOD(CompileShader) {
  glCompileShader(info[0]->Int32Value());
}

NAN_METHOD(FrontFace) {
  glFrontFace(info[0]->Int32Value());
}


NAN_METHOD(GetShaderParameter) {
  int shader = info[0]->Int32Value();
  int pname = info[1]->Int32Value();
  int value = 0;
  switch (pname) {
  case GL_DELETE_STATUS:
  case GL_COMPILE_STATUS:
    glGetShaderiv(shader, pname, &value);
    return info.GetReturnValue().Set(Nan::New(static_cast<bool>(value!=0)));
  case GL_SHADER_TYPE:
    glGetShaderiv(shader, pname, &value);
    return info.GetReturnValue().Set(Nan::New<Number>(static_cast<unsigned long>(value)));
  case GL_INFO_LOG_LENGTH:
  case GL_SHADER_SOURCE_LENGTH:
    glGetShaderiv(shader, pname, &value);
    return info.GetReturnValue().Set(Nan::New<Number>(static_cast<long>(value)));
  default:
    return Nan::ThrowTypeError("GetShaderParameter: Invalid Enum");
  }
}

NAN_METHOD(GetShaderInfoLog) {
  int id = info[0]->Int32Value();
  int Len = 1024;
  char Error[1024];
  glGetShaderInfoLog(id, 1024, &Len, Error);

  return info.GetReturnValue().Set(Nan::New(Error).ToLocalChecked());
}


NAN_METHOD(CreateProgram) {
  GLuint program=glCreateProgram();
  #ifdef LOGGING
  cout<<"createProgram "<<program<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_PROGRAM, program);
  return info.GetReturnValue().Set(Nan::New(program));
}


NAN_METHOD(AttachShader) {
  int program = info[0]->Int32Value();
  int shader = info[1]->Int32Value();

  glAttachShader(program, shader);
}


NAN_METHOD(LinkProgram) {
  glLinkProgram(info[0]->Int32Value());
}


NAN_METHOD(GetProgramParameter) {
  int program = info[0]->Int32Value();
  int pname = info[1]->Int32Value();

  int value = 0;
  switch (pname) {
  case GL_DELETE_STATUS:
  case GL_LINK_STATUS:
  case GL_VALIDATE_STATUS:
    glGetProgramiv(program, pname, &value);
    return info.GetReturnValue().Set(Nan::New(static_cast<bool>(value!=0)));
  case GL_ATTACHED_SHADERS:
  case GL_ACTIVE_ATTRIBUTES:
  case GL_ACTIVE_UNIFORMS:
    glGetProgramiv(program, pname, &value);
    return info.GetReturnValue().Set(Nan::New<Number>(static_cast<long>(value)));
  default:
    return Nan::ThrowTypeError("GetProgramParameter: Invalid Enum");
  }
}


NAN_METHOD(GetUniformLocation) {
  int program = info[0]->Int32Value();
  Nan::Utf8String name(info[1]);

  return info.GetReturnValue().Set(Nan::New(glGetUniformLocation(program, *name)));
}


NAN_METHOD(ClearColor) {
  float red = (float) info[0]->NumberValue();
  float green = (float) info[1]->NumberValue();
  float blue = (float) info[2]->NumberValue();
  float alpha = (float) info[3]->NumberValue();

  glClearColor(red, green, blue, alpha);
}


NAN_METHOD(ClearDepth) {
  float depth = (float) info[0]->NumberValue();

  glClearDepth(depth);
}

NAN_METHOD(Disable) {
  glDisable(info[0]->Int32Value());
}

NAN_METHOD(Enable) {
  glEnable(info[0]->Int32Value());
}


NAN_METHOD(CreateTexture) {
  GLuint texture;
  glGenTextures(1, &texture);
  #ifdef LOGGING
  cout<<"createTexture "<<texture<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_TEXTURE, texture);
  return info.GetReturnValue().Set(Nan::New(texture));
}


NAN_METHOD(BindTexture) {
  int target = info[0]->Int32Value();
  int texture = info[1]->IsNull() ? 0 : info[1]->Int32Value();

  glBindTexture(target, texture);
}


NAN_METHOD(TexImage2D) {
  int target = info[0]->Int32Value();
  int level = info[1]->Int32Value();
  int internalformat = info[2]->Int32Value();
  int width = info[3]->Int32Value();
  int height = info[4]->Int32Value();
  int border = info[5]->Int32Value();
  int format = info[6]->Int32Value();
  int type = info[7]->Int32Value();
  void *pixels=getImageData(info[8]);

  glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}


NAN_METHOD(TexParameteri) {
  int target = info[0]->Int32Value();
  int pname = info[1]->Int32Value();
  int param = info[2]->Int32Value();

  glTexParameteri(target, pname, param);
}

NAN_METHOD(TexParameterf) {
  int target = info[0]->Int32Value();
  int pname = info[1]->Int32Value();
  float param = (float) info[2]->NumberValue();

  glTexParameterf(target, pname, param);
}


NAN_METHOD(Clear) {
  glClear(info[0]->Int32Value());
}


NAN_METHOD(UseProgram) {
  glUseProgram(info[0]->Int32Value());
}

NAN_METHOD(CreateBuffer) {
  GLuint buffer;
  glGenBuffers(1, &buffer);
  #ifdef LOGGING
  cout<<"createBuffer "<<buffer<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_BUFFER, buffer);
  return info.GetReturnValue().Set(Nan::New(buffer));
}

NAN_METHOD(BindBuffer) {
  int target = info[0]->Int32Value();
  int buffer = info[1]->Uint32Value();
  glBindBuffer(target,buffer);
}


NAN_METHOD(CreateFramebuffer) {
  GLuint buffer;
  glGenFramebuffers(1, &buffer);
  #ifdef LOGGING
  cout<<"createFrameBuffer "<<buffer<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_FRAMEBUFFER, buffer);
  return info.GetReturnValue().Set(Nan::New(buffer));
}


NAN_METHOD(BindFramebuffer) {
  int target = info[0]->Int32Value();
  int buffer = info[1]->IsNull() ? 0 : info[1]->Int32Value();

  glBindFramebuffer(target, buffer);
}


NAN_METHOD(FramebufferTexture2D) {
  int target = info[0]->Int32Value();
  int attachment = info[1]->Int32Value();
  int textarget = info[2]->Int32Value();
  int texture = info[3]->Int32Value();
  int level = info[4]->Int32Value();

  glFramebufferTexture2D(target, attachment, textarget, texture, level);
}


NAN_METHOD(BufferData) {
  int target = info[0]->Int32Value();
  if(info[1]->IsObject()) {
    Local<Object> obj = Local<Object>::Cast(info[1]);
    GLenum usage = info[2]->Int32Value();

    Nan::TypedArrayContents<char> cont(obj);
    glBufferData(target, cont.length(), *cont, usage);
    // int element_size = SizeOfArrayElementForType(obj->GetIndexedPropertiesExternalArrayDataType());
    // GLsizeiptr size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
    // void* data = obj->GetIndexedPropertiesExternalArrayData();
    // glBufferData(target, size, data, usage);
  }
  else if(info[1]->IsNumber()) {
    GLsizeiptr size = info[1]->Uint32Value();
    GLenum usage = info[2]->Int32Value();
    glBufferData(target, size, NULL, usage);
  }
}


NAN_METHOD(BufferSubData) {
  int target = info[0]->Int32Value();
  int offset = info[1]->Int32Value();
  Local<Object> obj = Local<Object>::Cast(info[2]);

  Nan::TypedArrayContents<char> cont(obj);
  glBufferSubData(target, offset, cont.length(), *cont);

  // int element_size = SizeOfArrayElementForType( obj->GetIndexedPropertiesExternalArrayDataType());
  // int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
  // void* data = obj->GetIndexedPropertiesExternalArrayData();

  // glBufferSubData(target, offset, size, data);
}


NAN_METHOD(BlendEquation) {
  int mode=info[0]->Int32Value();;

  glBlendEquation(mode);
}


NAN_METHOD(BlendFunc) {
  int sfactor=info[0]->Int32Value();;
  int dfactor=info[1]->Int32Value();;

  glBlendFunc(sfactor,dfactor);
}


NAN_METHOD(EnableVertexAttribArray) {
  glEnableVertexAttribArray(info[0]->Int32Value());
}


NAN_METHOD(VertexAttribPointer) {
  int indx = info[0]->Int32Value();
  int size = info[1]->Int32Value();
  int type = info[2]->Int32Value();
  int normalized = info[3]->BooleanValue();
  int stride = info[4]->Int32Value();
  int offset = info[5]->Int32Value();

  //    printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
  glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid *)(intptr_t)offset);
}


NAN_METHOD(ActiveTexture) {
  glActiveTexture(info[0]->Int32Value());
}


NAN_METHOD(DrawElements) {
  int mode = info[0]->Int32Value();
  int count = info[1]->Int32Value();
  int type = info[2]->Int32Value();
  GLvoid *offset = reinterpret_cast<GLvoid*>(info[3]->Uint32Value());
  glDrawElements(mode, count, type, offset);
}


NAN_METHOD(Flush) {
  glFlush();
}

NAN_METHOD(Finish) {
  glFinish();
}

NAN_METHOD(VertexAttrib1f) {
  GLuint indx = info[0]->Int32Value();
  float x = (float) info[1]->NumberValue();

  glVertexAttrib1f(indx, x);
}

NAN_METHOD(VertexAttrib2f) {
  GLuint indx = info[0]->Int32Value();
  float x = (float) info[1]->NumberValue();
  float y = (float) info[2]->NumberValue();

  glVertexAttrib2f(indx, x, y);
}

NAN_METHOD(VertexAttrib3f) {
  GLuint indx = info[0]->Int32Value();
  float x = (float) info[1]->NumberValue();
  float y = (float) info[2]->NumberValue();
  float z = (float) info[3]->NumberValue();

  glVertexAttrib3f(indx, x, y, z);
}

NAN_METHOD(VertexAttrib4f) {
  GLuint indx = info[0]->Int32Value();
  float x = (float) info[1]->NumberValue();
  float y = (float) info[2]->NumberValue();
  float z = (float) info[3]->NumberValue();
  float w = (float) info[4]->NumberValue();

  glVertexAttrib4f(indx, x, y, z, w);
}

NAN_METHOD(VertexAttrib1fv) {
  int indx = info[0]->Int32Value();
  GLfloat *data = getArrayData<GLfloat>(info[1]);
  glVertexAttrib1fv(indx, data);
}

NAN_METHOD(VertexAttrib2fv) {
  int indx = info[0]->Int32Value();
  GLfloat *data = getArrayData<GLfloat>(info[1]);
  glVertexAttrib2fv(indx, data);
}

NAN_METHOD(VertexAttrib3fv) {
  int indx = info[0]->Int32Value();
  GLfloat *data = getArrayData<GLfloat>(info[1]);
  glVertexAttrib3fv(indx, data);
}

NAN_METHOD(VertexAttrib4fv) {
  int indx = info[0]->Int32Value();
  GLfloat *data = getArrayData<GLfloat>(info[1]);
  glVertexAttrib4fv(indx, data);
}

NAN_METHOD(BlendColor) {
  GLclampf r= (float) info[0]->NumberValue();
  GLclampf g= (float) info[1]->NumberValue();
  GLclampf b= (float) info[2]->NumberValue();
  GLclampf a= (float) info[3]->NumberValue();

  glBlendColor(r,g,b,a);
}

NAN_METHOD(BlendEquationSeparate) {
  GLenum modeRGB= info[0]->Int32Value();
  GLenum modeAlpha= info[1]->Int32Value();

  glBlendEquationSeparate(modeRGB,modeAlpha);
}

NAN_METHOD(BlendFuncSeparate) {
  GLenum srcRGB= info[0]->Int32Value();
  GLenum dstRGB= info[1]->Int32Value();
  GLenum srcAlpha= info[2]->Int32Value();
  GLenum dstAlpha= info[3]->Int32Value();

  glBlendFuncSeparate(srcRGB,dstRGB,srcAlpha,dstAlpha);
}

NAN_METHOD(ClearStencil) {
  GLint s = info[0]->Int32Value();

  glClearStencil(s);
}

NAN_METHOD(ColorMask) {
  GLboolean r = info[0]->BooleanValue();
  GLboolean g = info[1]->BooleanValue();
  GLboolean b = info[2]->BooleanValue();
  GLboolean a = info[3]->BooleanValue();

  glColorMask(r,g,b,a);
}

NAN_METHOD(CopyTexImage2D) {
  GLenum target = info[0]->Int32Value();
  GLint level = info[1]->Int32Value();
  GLenum internalformat = info[2]->Int32Value();
  GLint x = info[3]->Int32Value();
  GLint y = info[4]->Int32Value();
  GLsizei width = info[5]->Int32Value();
  GLsizei height = info[6]->Int32Value();
  GLint border = info[7]->Int32Value();

  glCopyTexImage2D( target, level, internalformat, x, y, width, height, border);
}

NAN_METHOD(CopyTexSubImage2D) {
  GLenum target = info[0]->Int32Value();
  GLint level = info[1]->Int32Value();
  GLint xoffset = info[2]->Int32Value();
  GLint yoffset = info[3]->Int32Value();
  GLint x = info[4]->Int32Value();
  GLint y = info[5]->Int32Value();
  GLsizei width = info[6]->Int32Value();
  GLsizei height = info[7]->Int32Value();

  glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, width, height);
}

NAN_METHOD(CullFace) {
  GLenum mode = info[0]->Int32Value();

  glCullFace(mode);
}

NAN_METHOD(DepthMask) {
  GLboolean flag = info[0]->BooleanValue();

  glDepthMask(flag);
}

NAN_METHOD(DepthRange) {
  GLclampf zNear = (float) info[0]->NumberValue();
  GLclampf zFar = (float) info[1]->NumberValue();

  glDepthRangef(zNear, zFar);
}

NAN_METHOD(DisableVertexAttribArray) {
  GLuint index = info[0]->Int32Value();

  glDisableVertexAttribArray(index);
}

NAN_METHOD(Hint) {
  GLenum target = info[0]->Int32Value();
  GLenum mode = info[1]->Int32Value();

  glHint(target, mode);
}

NAN_METHOD(IsEnabled) {
  GLenum cap = info[0]->Int32Value();

  bool ret=glIsEnabled(cap)!=0;
  return info.GetReturnValue().Set(Nan::New(ret));
}

NAN_METHOD(LineWidth) {
  GLfloat width = (float) info[0]->NumberValue();

  glLineWidth(width);
}

NAN_METHOD(PolygonOffset) {
  GLfloat factor = (float) info[0]->NumberValue();
  GLfloat units = (float) info[1]->NumberValue();

  glPolygonOffset(factor, units);
}

NAN_METHOD(SampleCoverage) {
  GLclampf value = (float) info[0]->NumberValue();
  GLboolean invert = info[1]->BooleanValue();

  glSampleCoverage(value, invert);
}

NAN_METHOD(Scissor) {
  GLint x = info[0]->Int32Value();
  GLint y = info[1]->Int32Value();
  GLsizei width = info[2]->Int32Value();
  GLsizei height = info[3]->Int32Value();

  glScissor(x, y, width, height);
}

NAN_METHOD(StencilFunc) {
  GLenum func = info[0]->Int32Value();
  GLint ref = info[1]->Int32Value();
  GLuint mask = info[2]->Int32Value();

  glStencilFunc(func, ref, mask);
}

NAN_METHOD(StencilFuncSeparate) {
  GLenum face = info[0]->Int32Value();
  GLenum func = info[1]->Int32Value();
  GLint ref = info[2]->Int32Value();
  GLuint mask = info[3]->Int32Value();

  glStencilFuncSeparate(face, func, ref, mask);
}

NAN_METHOD(StencilMask) {
  GLuint mask = info[0]->Uint32Value();

  glStencilMask(mask);
}

NAN_METHOD(StencilMaskSeparate) {
  GLenum face = info[0]->Int32Value();
  GLuint mask = info[1]->Uint32Value();

  glStencilMaskSeparate(face, mask);
}

NAN_METHOD(StencilOp) {
  GLenum fail = info[0]->Int32Value();
  GLenum zfail = info[1]->Int32Value();
  GLenum zpass = info[2]->Int32Value();

  glStencilOp(fail, zfail, zpass);
}

NAN_METHOD(StencilOpSeparate) {
  GLenum face = info[0]->Int32Value();
  GLenum fail = info[1]->Int32Value();
  GLenum zfail = info[2]->Int32Value();
  GLenum zpass = info[3]->Int32Value();

  glStencilOpSeparate(face, fail, zfail, zpass);
}

NAN_METHOD(BindRenderbuffer) {
  GLenum target = info[0]->Int32Value();
  GLuint buffer = info[1]->IsNull() ? 0 : info[1]->Int32Value();

  glBindRenderbuffer(target, buffer);
}

NAN_METHOD(CreateRenderbuffer) {
  GLuint renderbuffers;
  glGenRenderbuffers(1,&renderbuffers);
  #ifdef LOGGING
  cout<<"createRenderBuffer "<<renderbuffers<<endl;
  #endif
  registerGLObj(GLOBJECT_TYPE_RENDERBUFFER, renderbuffers);
  return info.GetReturnValue().Set(Nan::New(renderbuffers));
}

NAN_METHOD(DeleteBuffer) {
  GLuint buffer = info[0]->Uint32Value();

  glDeleteBuffers(1,&buffer);
}

NAN_METHOD(DeleteFramebuffer) {
  GLuint buffer = info[0]->Uint32Value();

  glDeleteFramebuffers(1,&buffer);
}

NAN_METHOD(DeleteProgram) {
  GLuint program = info[0]->Uint32Value();

  glDeleteProgram(program);
}

NAN_METHOD(DeleteRenderbuffer) {
  GLuint renderbuffer = info[0]->Uint32Value();

  glDeleteRenderbuffers(1, &renderbuffer);
}

NAN_METHOD(DeleteShader) {
  GLuint shader = info[0]->Uint32Value();

  glDeleteShader(shader);
}

NAN_METHOD(DeleteTexture) {
  GLuint texture = info[0]->Uint32Value();

  glDeleteTextures(1,&texture);
}

NAN_METHOD(DetachShader) {
  GLuint program = info[0]->Uint32Value();
  GLuint shader = info[1]->Uint32Value();

  glDetachShader(program, shader);
}

NAN_METHOD(FramebufferRenderbuffer) {
  GLenum target = info[0]->Int32Value();
  GLenum attachment = info[1]->Int32Value();
  GLenum renderbuffertarget = info[2]->Int32Value();
  GLuint renderbuffer = info[3]->Uint32Value();

  glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

NAN_METHOD(GetVertexAttribOffset) {
  GLuint index = info[0]->Uint32Value();
  GLenum pname = info[1]->Int32Value();
  void *ret=NULL;

  glGetVertexAttribPointerv(index, pname, &ret);
  return info.GetReturnValue().Set(Nan::New(ToGLuint(ret)));
}

NAN_METHOD(IsBuffer) {
  return info.GetReturnValue().Set(Nan::New(glIsBuffer(info[0]->Uint32Value())!=0));
}

NAN_METHOD(IsFramebuffer) {
  return info.GetReturnValue().Set(Nan::New(glIsFramebuffer(info[0]->Uint32Value())!=0));
}

NAN_METHOD(IsProgram) {
  return info.GetReturnValue().Set(Nan::New(glIsProgram(info[0]->Uint32Value())!=0));
}

NAN_METHOD(IsRenderbuffer) {
  return info.GetReturnValue().Set(Nan::New(glIsRenderbuffer( info[0]->Uint32Value())!=0));
}

NAN_METHOD(IsShader) {
  return info.GetReturnValue().Set(Nan::New(glIsShader(info[0]->Uint32Value())!=0));
}

NAN_METHOD(IsTexture) {
  return info.GetReturnValue().Set(Nan::New(glIsTexture(info[0]->Uint32Value())!=0));
}

NAN_METHOD(RenderbufferStorage) {
  GLenum target = info[0]->Int32Value();
  GLenum internalformat = info[1]->Int32Value();
  GLsizei width = info[2]->Uint32Value();
  GLsizei height = info[3]->Uint32Value();

  glRenderbufferStorage(target, internalformat, width, height);
}

NAN_METHOD(GetShaderSource) {
  int shader = info[0]->Int32Value();

  GLint len;
  glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
  GLchar *source=new GLchar[len];
  glGetShaderSource(shader, len, NULL, source);

  Local<String> str=Nan::New(source).ToLocalChecked();
  delete source;

  return info.GetReturnValue().Set(str);
}

NAN_METHOD(ValidateProgram) {
  glValidateProgram(info[0]->Int32Value());

}

NAN_METHOD(TexSubImage2D) {
  GLenum target = info[0]->Int32Value();
  GLint level = info[1]->Int32Value();
  GLint xoffset = info[2]->Int32Value();
  GLint yoffset = info[3]->Int32Value();
  GLsizei width = info[4]->Int32Value();
  GLsizei height = info[5]->Int32Value();
  GLenum format = info[6]->Int32Value();
  GLenum type = info[7]->Int32Value();
  void *pixels=getImageData(info[8]);

  glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

NAN_METHOD(ReadPixels) {
  GLint x = info[0]->Int32Value();
  GLint y = info[1]->Int32Value();
  GLsizei width = info[2]->Int32Value();
  GLsizei height = info[3]->Int32Value();
  GLenum format = info[4]->Int32Value();
  GLenum type = info[5]->Int32Value();
  void *pixels=getImageData(info[6]);

  glReadPixels(x, y, width, height, format, type, pixels);
}

NAN_METHOD(GetTexParameter) {
  GLenum target = info[0]->Int32Value();
  GLenum pname = info[1]->Int32Value();

  GLint param_value=0;
  glGetTexParameteriv(target, pname, &param_value);

  return info.GetReturnValue().Set(Nan::New(param_value));
}

NAN_METHOD(GetActiveAttrib) {
  GLuint program = info[0]->Int32Value();
  GLuint index = info[1]->Int32Value();

  char name[1024];
  GLsizei length=0;
  GLenum type;
  GLsizei size;
  glGetActiveAttrib(program, index, 1024, &length, &size, &type, name);

  Local<Array> activeInfo = Nan::New<Array>(3);
  activeInfo->Set(Nan::New("size").ToLocalChecked(), Nan::New(size));
  activeInfo->Set(Nan::New("type").ToLocalChecked(), Nan::New((int)type));
  activeInfo->Set(Nan::New("name").ToLocalChecked(), Nan::New(name).ToLocalChecked());

  return info.GetReturnValue().Set(activeInfo);
}

NAN_METHOD(GetActiveUniform) {
  GLuint program = info[0]->Int32Value();
  GLuint index = info[1]->Int32Value();

  char name[1024];
  GLsizei length=0;
  GLenum type;
  GLsizei size;
  glGetActiveUniform(program, index, 1024, &length, &size, &type, name);

  Local<Array> activeInfo = Nan::New<Array>(3);
  activeInfo->Set(Nan::New("size").ToLocalChecked(), Nan::New(size));
  activeInfo->Set(Nan::New("type").ToLocalChecked(), Nan::New((int)type));
  activeInfo->Set(Nan::New("name").ToLocalChecked(), Nan::New(name).ToLocalChecked());

  return info.GetReturnValue().Set(activeInfo);
}

NAN_METHOD(GetAttachedShaders) {
  GLuint program = info[0]->Int32Value();

  GLuint shaders[1024];
  GLsizei count;
  glGetAttachedShaders(program, 1024, &count, shaders);

  Local<Array> shadersArr = Nan::New<Array>(count);
  for(int i=0;i<count;i++)
    shadersArr->Set(i, Nan::New((int)shaders[i]));

  return info.GetReturnValue().Set(shadersArr);
}

NAN_METHOD(GetParameter) {
  GLenum name = info[0]->Int32Value();

  switch(name) {
  case GL_BLEND:
  case GL_CULL_FACE:
  case GL_DEPTH_TEST:
  case GL_DEPTH_WRITEMASK:
  case GL_DITHER:
  case GL_POLYGON_OFFSET_FILL:
  case GL_SAMPLE_COVERAGE_INVERT:
  case GL_SCISSOR_TEST:
  case GL_STENCIL_TEST:
  case 0x9240 /* UNPACK_FLIP_Y_WEBGL */:
  case 0x9241 /* UNPACK_PREMULTIPLY_ALPHA_WEBGL*/:
  {
    // return a boolean
    GLboolean params;
    ::glGetBooleanv(name, &params);
    return info.GetReturnValue().Set(Nan::New(params!=0));
  }
  case GL_DEPTH_CLEAR_VALUE:
  case GL_LINE_WIDTH:
  case GL_POLYGON_OFFSET_FACTOR:
  case GL_POLYGON_OFFSET_UNITS:
  case GL_SAMPLE_COVERAGE_VALUE:
  {
    // return a float
    GLfloat params;
    ::glGetFloatv(name, &params);
    return info.GetReturnValue().Set(Nan::New(params));
  }
  case GL_RENDERER:
  case GL_SHADING_LANGUAGE_VERSION:
  case GL_VENDOR:
  case GL_VERSION:
  case GL_EXTENSIONS:
  {
    // return a string
    char *params=(char*) ::glGetString(name);
    if(params)
      return info.GetReturnValue().Set(Nan::New(params).ToLocalChecked());
    return;
  }
  case GL_MAX_VIEWPORT_DIMS:
  {
    // return a int32[2]
    GLint params[2];
    ::glGetIntegerv(name, params);

    Local<Array> arr=Nan::New<Array>(2);
    arr->Set(0,Nan::New(params[0]));
    arr->Set(1,Nan::New(params[1]));
    return info.GetReturnValue().Set(arr);
  }
  case GL_SCISSOR_BOX:
  case GL_VIEWPORT:
  {
    // return a int32[4]
    GLint params[4];
    ::glGetIntegerv(name, params);

    Local<Array> arr=Nan::New<Array>(4);
    arr->Set(0,Nan::New(params[0]));
    arr->Set(1,Nan::New(params[1]));
    arr->Set(2,Nan::New(params[2]));
    arr->Set(3,Nan::New(params[3]));
    return info.GetReturnValue().Set(arr);
  }
  case GL_ALIASED_LINE_WIDTH_RANGE:
  case GL_ALIASED_POINT_SIZE_RANGE:
  case GL_DEPTH_RANGE:
  {
    // return a float[2]
    GLfloat params[2];
    ::glGetFloatv(name, params);
    Local<Array> arr=Nan::New<Array>(2);
    arr->Set(0,Nan::New(params[0]));
    arr->Set(1,Nan::New(params[1]));
    return info.GetReturnValue().Set(arr);
  }
  case GL_BLEND_COLOR:
  case GL_COLOR_CLEAR_VALUE:
  {
    // return a float[4]
    GLfloat params[4];
    ::glGetFloatv(name, params);
    Local<Array> arr=Nan::New<Array>(4);
    arr->Set(0,Nan::New(params[0]));
    arr->Set(1,Nan::New(params[1]));
    arr->Set(2,Nan::New(params[2]));
    arr->Set(3,Nan::New(params[3]));
    return info.GetReturnValue().Set(arr);
  }
  case GL_COLOR_WRITEMASK:
  {
    // return a boolean[4]
    GLboolean params[4];
    ::glGetBooleanv(name, params);
    Local<Array> arr=Nan::New<Array>(4);
    arr->Set(0,Nan::New(params[0]==1));
    arr->Set(1,Nan::New(params[1]==1));
    arr->Set(2,Nan::New(params[2]==1));
    arr->Set(3,Nan::New(params[3]==1));
    return info.GetReturnValue().Set(arr);
  }
  case GL_ARRAY_BUFFER_BINDING:
  case GL_CURRENT_PROGRAM:
  case GL_ELEMENT_ARRAY_BUFFER_BINDING:
  case GL_FRAMEBUFFER_BINDING:
  case GL_RENDERBUFFER_BINDING:
  case GL_TEXTURE_BINDING_2D:
  case GL_TEXTURE_BINDING_CUBE_MAP:
  {
    GLint params;
    ::glGetIntegerv(name, &params);
    return info.GetReturnValue().Set(Nan::New(params));
  }
  default: {
    // return a long
    GLint params;
    ::glGetIntegerv(name, &params);
    return info.GetReturnValue().Set(Nan::New(params));
  }
  }
}

NAN_METHOD(GetBufferParameter) {
  GLenum target = info[0]->Int32Value();
  GLenum pname = info[1]->Int32Value();

  GLint params;
  glGetBufferParameteriv(target,pname,&params);
  return info.GetReturnValue().Set(Nan::New(params));
}

NAN_METHOD(GetFramebufferAttachmentParameter) {
  GLenum target = info[0]->Int32Value();
  GLenum attachment = info[1]->Int32Value();
  GLenum pname = info[2]->Int32Value();

  GLint params;
  glGetFramebufferAttachmentParameteriv(target,attachment, pname,&params);
  return info.GetReturnValue().Set(Nan::New(params));
}

NAN_METHOD(GetProgramInfoLog) {
  GLuint program = info[0]->Int32Value();
  int Len = 1024;
  char Error[1024];
  glGetProgramInfoLog(program, 1024, &Len, Error);

  return info.GetReturnValue().Set(Nan::New(Error).ToLocalChecked());
}

NAN_METHOD(GetRenderbufferParameter) {
  int target = info[0]->Int32Value();
  int pname = info[1]->Int32Value();
  int value = 0;
  glGetRenderbufferParameteriv(target,pname,&value);

  return info.GetReturnValue().Set(Nan::New(value));
}

NAN_METHOD(GetUniform) {
  GLuint program = info[0]->Int32Value();
  GLint location = info[1]->Int32Value();
  if(location < 0 ) return;

  float data[16]; // worst case scenario is 16 floats

  glGetUniformfv(program, location, data);

  Local<Array> arr=Nan::New<Array>(16);
  for(int i=0;i<16;i++)
    arr->Set(i,Nan::New(data[i]));

  return info.GetReturnValue().Set(arr);
}

NAN_METHOD(GetVertexAttrib) {
  GLuint index = info[0]->Int32Value();
  GLuint pname = info[1]->Int32Value();

  GLint value=0;

  switch (pname) {
  case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
  case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
    glGetVertexAttribiv(index,pname,&value);
    return info.GetReturnValue().Set(Nan::New(value!=0));
  case GL_VERTEX_ATTRIB_ARRAY_SIZE:
  case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
  case GL_VERTEX_ATTRIB_ARRAY_TYPE:
    glGetVertexAttribiv(index,pname,&value);
    return info.GetReturnValue().Set(Nan::New(value));
  case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
    glGetVertexAttribiv(index,pname,&value);
    return info.GetReturnValue().Set(Nan::New(value));
  case GL_CURRENT_VERTEX_ATTRIB: {
    float vextex_attribs[4];
    glGetVertexAttribfv(index,pname,vextex_attribs);
    Local<Array> arr=Nan::New<Array>(4);
    arr->Set(0,Nan::New(vextex_attribs[0]));
    arr->Set(1,Nan::New(vextex_attribs[1]));
    arr->Set(2,Nan::New(vextex_attribs[2]));
    arr->Set(3,Nan::New(vextex_attribs[3]));
    return info.GetReturnValue().Set(arr);
  }
  default:
    Nan::ThrowError("GetVertexAttrib: Invalid Enum");
  }
}

NAN_METHOD(GetSupportedExtensions) {
  char *extensions=(char*) glGetString(GL_EXTENSIONS);

  return info.GetReturnValue().Set(Nan::New(extensions).ToLocalChecked());
}

// TODO GetExtension(name) return the extension name if found, should be an object...
NAN_METHOD(GetExtension) {
  return;

  // TODO
  /*NanAsciiString name(info[0]);
  char *sname=*name;
  char *extensions=(char*) glGetString(GL_EXTENSIONS);

  char *ext=strcasestr(extensions, sname);

  if(!ext) return info.GetReturnValue().Set(Nan::Undefined());
  return info.GetReturnValue().Set(Nan::New(ext, (int)::strlen(sname)).ToLocalChecked());*/
}

NAN_METHOD(CheckFramebufferStatus) {
  GLenum target=info[0]->Int32Value();

  return info.GetReturnValue().Set(Nan::New((int)glCheckFramebufferStatus(target)));
}

struct GLObj {
  GLObjectType type;
  GLuint obj;
  GLObj(GLObjectType type, GLuint obj) {
    this->type=type;
    this->obj=obj;
  }
};

vector<GLObj*> globjs;
static bool atExit=false;

void registerGLObj(GLObjectType type, GLuint obj) {
  globjs.push_back(new GLObj(type,obj));
}


void unregisterGLObj(GLuint obj) {
  if(atExit) return;

  vector<GLObj*>::iterator it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *globj=*it;
    if(globj->obj==obj) {
      delete globj;
      globjs.erase(it);
      break;
    }
    ++it;
  }
}

void AtExit() {
  atExit=true;
  //glFinish();

  vector<GLObj*>::iterator it;

  #ifdef LOGGING
  cout<<"WebGL AtExit() called"<<endl;
  cout<<"  # objects allocated: "<<globjs.size()<<endl;
  it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *obj=*it;
    cout<<"[";
    switch(obj->type) {
    case GLOBJECT_TYPE_BUFFER: cout<<"buffer"; break;
    case GLOBJECT_TYPE_FRAMEBUFFER: cout<<"framebuffer"; break;
    case GLOBJECT_TYPE_PROGRAM: cout<<"program"; break;
    case GLOBJECT_TYPE_RENDERBUFFER: cout<<"renderbuffer"; break;
    case GLOBJECT_TYPE_SHADER: cout<<"shader"; break;
    case GLOBJECT_TYPE_TEXTURE: cout<<"texture"; break;
    };
    cout<<": "<<obj->obj<<"] ";
    ++it;
  }
  cout<<endl;
  #endif

  it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *globj=*it;
    GLuint obj=globj->obj;

    switch(globj->type) {
    case GLOBJECT_TYPE_PROGRAM:
      #ifdef LOGGING
      cout<<"  Destroying GL program "<<obj<<endl;
      #endif
      glDeleteProgram(obj);
      break;
    case GLOBJECT_TYPE_BUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL buffer "<<obj<<endl;
      #endif
      glDeleteBuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_FRAMEBUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL frame buffer "<<obj<<endl;
      #endif
      glDeleteFramebuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_RENDERBUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL render buffer "<<obj<<endl;
      #endif
      glDeleteRenderbuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_SHADER:
      #ifdef LOGGING
      cout<<"  Destroying GL shader "<<obj<<endl;
      #endif
      glDeleteShader(obj);
      break;
    case GLOBJECT_TYPE_TEXTURE:
      #ifdef LOGGING
      cout<<"  Destroying GL texture "<<obj<<endl;
      #endif
      glDeleteTextures(1,&obj);
      break;
    default:
      #ifdef LOGGING
      cout<<"  Unknown object "<<obj<<endl;
      #endif
      break;
    }
    delete globj;
    ++it;
  }

  globjs.clear();
}

} // end namespace webgl
