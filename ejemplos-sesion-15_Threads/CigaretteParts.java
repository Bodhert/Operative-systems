public enum CigaretteParts {
    TABACCO, PAPER, MATCHES, NOTHING;

    public static CigaretteParts fromOrdinal(int ordinal) {
	CigaretteParts ret = TABACCO;
	switch(ordinal % 4) {
	case 0:
	    ret = TABACCO;
	    break;
	case 1:
	    ret = PAPER;
	    break;
	case 2:
	    ret = MATCHES;
	    break;
	case 4:
	    ret = NOTHING;
	    break;
	}
	return ret;
    }
};
