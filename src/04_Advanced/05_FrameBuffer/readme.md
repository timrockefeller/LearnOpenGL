```c
GLenum glCheckFramebufferStatus(GLenum target);
GLenum glCheckNamedFramebufferStatus(GLuint framebuffer,GLenum target);
```

The return value is `GL_FRAMEBUFFER_COMPLETE` if the specified framebuffer is complete. Otherwise, the return value is determined as follows:

- `GL_FRAMEBUFFER_UNDEFINED` is returned if the specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist.
- `GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT` is returned if any of the framebuffer attachment points are framebuffer incomplete.
- `GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT` is returned if the framebuffer does not have at least one image attached to it.
- `GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER` is returned if the value of `GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE` is `GL_NONE` for any color attachment point(s) named by `GL_DRAW_BUFFERi`.
- `GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER` is returned if `GL_READ_BUFFER` is not `GL_NONE` and the value of `GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE` is `GL_NONE` for the color attachment point named by `GL_READ_BUFFER`.
- `GL_FRAMEBUFFER_UNSUPPORTED` is returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions.
- `GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE` is returned if the value of `GL_RENDERBUFFER_SAMPLES` is not the same for all attached renderbuffers; if the value of `GL_TEXTURE_SAMPLES` is the not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of `GL_RENDERBUFFER_SAMPLES` does not match the value of `GL_TEXTURE_SAMPLES`.
- `GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE` is also returned if the value of `GL_TEXTURE_FIXED_SAMPLE_LOCATIONS` is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of `GL_TEXTURE_FIXED_SAMPLE_LOCATIONS` is not `GL_TRUE` for all attached textures.
- `GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS` is returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target.