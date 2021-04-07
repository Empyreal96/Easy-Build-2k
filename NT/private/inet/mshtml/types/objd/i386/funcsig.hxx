BOOL DispNonDualDIID(IID iid);
typedef HRESULT (*CustomHandler)(CBase *pBase,
                                 IServiceProvider *pSrvProvider,
                                 IDispatch *pInstance,
                                 WORD wVTblOffset,
                                 PROPERTYDESC_BASIC_ABSTRACT *pDesc,
                                 WORD wFlags,
                                 DISPPARAMS *pdispparams,
                                 VARIANT *pvarResult);



