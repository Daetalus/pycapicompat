#ifndef _PYCAPICOMPAT_H_
#define _PYCAPICOMPAT_H_

/* pycapicompat.h - Extra CAPI functions for compatibility between various C-based Python implementations
 * Copyright (C) 2016 Nexedi SA and Contributors.
 * This file is licensed under the MIT license:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ~~~~~~~~
 *
 * The recommended way to use pycapicompat.h is to copy it from canonical
 * location to your project on as-needed basis and include locally.
 *
 * The canonical location is:
 *
 *   https://lab.nexedi.com/nexedi/pycapicompat/raw/master/pycapicompat.h
 *   (or https://lab.nexedi.com/nexedi/pycapicompat.git for Git access)
 *
 * Last updated: 2016-06-13
 */

#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO(Daetalus)
#ifdef IMPLEMENTATION_SUPPORTS_EXTENDED_C_API

#else
#define PyErr_GetExcInfoType() PyThreadState_GET()->exc_type;
// info about free variables
#define PyCode_HasFreeVars(co) PyCode_GetNumFree((PyCodeObject *)co) > 0
#define PyFrame_SetLineNumber(py_frame, py_line); py_frame->f_lineno = py_line;
#define PyFrame_SetBack(frame, back) frame->f_back = back;
#define PyObject* PyErr_GetExcInfoType() PyThreadState_GET()->exc_type;

extern "C" PyObject* PyErr_GetExcInfoValue() noexcept {
    ExcInfo exc = getFrameExcInfo();
    return exc->value;
}

extern "C" PyObject* PyErr_GetExcTraceback() noexcept {
    ExcInfo exc = getFrameExcInfo();
    return exc->traceback;
}
#endif

#ifdef __cplusplus
}
#endif

#endif
