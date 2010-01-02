#ifndef BUSYCURSOR_H
#define BUSYCURSOR_H

class CBusyCursor
{
public:
	CBusyCursor(BOOL fBusy = TRUE) { if (fBusy) Busy(); else m_hOldCursor = NULL; };
	~CBusyCursor() { NotBusy(); };

	// Note:  This should be changed to use class variable ref-counting on the wait cursor to avoid cursor weirdness
	void Busy() { m_hOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT)); };
	void NotBusy() { SetCursor(m_hOldCursor); };

private:
	HCURSOR		m_hOldCursor;
};

#endif	// BUSYCURSOR_H