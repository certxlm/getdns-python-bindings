
#include "pygetdns_ext_libuv.h"
#include <stdio.h>

extern PyTypeObject getdns_ContextType;

PyTypeObject getdns_UVContextType = {
#if PY_MAJOR_VERSION >= 3
    PyVarObject_HEAD_INIT(NULL, 0)
#else
    PyObject_HEAD_INIT(NULL)
    0,
#endif
    "getdns.UVContext",
    sizeof(getdns_UVContextObject),
    0,                         /*tp_itemsize*/
    (destructor)uvcontext_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,       /*tp_flags*/
    "UV Context object",       /* tp_doc */
    0,                         /* tp_traverse       */
    0,                         /* tp_clear          */
    0,                         /* tp_richcompare    */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter           */
    0,                         /* tp_iternext       */
    UVContext_methods,         /* tp_methods        */
    0,                         /* tp_members        */
    0,                         /* tp_getset         */
    &getdns_ContextType,       /* tp_base           */
    0,                         /* tp_dict           */
    0,                         /* tp_descr_get      */
    0,                         /* tp_descr_set      */
    0,                         /* tp_dictoffset     */
    (initproc)uvcontext_init,  /* tp_init           */
};

static PyMethodDef UVContext_methods[] = {
  /*
  { "run", (PyCFunction)uvcontext_run, METH_VARARGS|METH_KEYWORDS,
    "run unprocessed events with uvloop" },
    */
  { NULL }
};

int
uvcontext_init(getdns_UVContextObject *self, PyObject *args, PyObject *keywds)
{

  getdns_return_t r;

  if (getdns_ContextType.tp_init((PyObject *)self,  args, keywds) < 0) {
    return -1;
  }

  if (uv_loop_init(&(self->loop))) {
    return -1;
  }

  if ((r = getdns_extension_set_libuv_loop((self->context).context, &(self->loop))))
    fprintf( stderr, "Unable to set the event loop: %s\n"
             , getdns_get_errorstr_by_id(r));

  return 0;

}

PyObject *
uvcontext_run(getdns_UVContextObject *self, PyObject *args, PyObject *keywds)
{
  uv_run(&(self->loop), UV_RUN_DEFAULT);
  Py_RETURN_NONE;
}

void
uvcontext_dealloc(getdns_UVContextObject *self)
{
  uv_stop(&(self->loop));
  uv_loop_close(&(self->loop));
  getdns_ContextType.tp_dealloc((PyObject *)self);
}


