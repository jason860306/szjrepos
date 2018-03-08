#include "framecommon/atomic32.h"
#include "fastcounter.h"

int main(int /*argc*/, char */*argv*/[])
{
	CCounter *pcnter = NULL;
	pcnter = new CCounter(0, "cnttest");
	pcnter->Count(1);
	pcnter->GetCount(true);
	pcnter->GetType();
	pcnter->GetTypeName();

	CFastCounter *pfastcnter = NULL;
	pfastcnter = new CFastCounter();
	pfastcnter->Init("fastcntertest", 3);
	char tmp_buf[100] = { 0 };
	for (int i = 0; i < 3; ++i) {
		snprintf(tmp_buf, sizeof(tmp_buf), "cmd_%02d", i);
		pfastcnter->AddCounter(i, tmp_buf);
	}
	pfastcnter->Count(1);
	pfastcnter->Count(2);
	pfastcnter->WriteLog(INFORUNTYPE, true);
}
