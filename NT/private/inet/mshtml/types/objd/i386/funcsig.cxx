

static const CustomHandler  _HandlerTable[] = {
   NULL
};




#define MAX_IIDS 1
static const IID * _IIDTable[MAX_IIDS] = {
	NULL,
};

#define DIID_DispBase   0x3050f500
#define DIID_DispMax    0x3050f5a0

const GUID DIID_Low12Bytes = { 0x00000000, 0x98b5, 0x11cf, { 0xbb, 0x82, 0x00, 0xaa, 0x00, 0xbd, 0xce, 0x0b } };


BOOL DispNonDualDIID(IID iid)
{
	BOOL    fRetVal = FALSE;

	if (iid.Data1 >= DIID_DispBase && iid.Data1 <= DIID_DispMax)
	{
		fRetVal = memcmp(&iid.Data2,
				&DIID_Low12Bytes.Data2,
				sizeof(IID) - sizeof(DWORD)) == 0;
	}

	return fRetVal;
}

