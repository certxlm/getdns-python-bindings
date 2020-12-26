/*
 * defines for pygetdns UVContext subtype
 */
#ifndef PYGETDNS_EX_UV_H
#define PYGETDNS_EX_UV_H 

#include <Python.h>
#include <getdns/getdns.h>
#include <getdns/getdns_extra.h>
#include <getdns/getdns_ext_libuv.h>
#include <uv.h>
#include "pygetdns.h"
typedef struct {
  getdns_ContextObject context;
  uv_loop_t loop;
} getdns_UVContextObject;

static int  uvcontext_init(getdns_UVContextObject *self, PyObject *args, PyObject *keywds);
static void uvcontext_dealloc(getdns_UVContextObject *self);
static PyObject *uvcontext_run(getdns_UVContextObject *self, PyObject *args, PyObject *keywds);
static PyMethodDef UVContext_methods[];

#endif /* PYGETDNS_EX_UV_H */
