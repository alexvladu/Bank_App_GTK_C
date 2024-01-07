#ifndef external_files
#define external_files
void create_pdf(int *cardid)
{
	struct Card card=get_card_by_id(*cardid);
    FILE *pdfFile = fopen("Extern_File/card_info_generated.pdf", "w");
    fprintf(pdfFile,
            "%%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /Resources << /Font << /F1 4 0 R >> >> /Contents 5 0 R >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Type /Font /Subtype /Type1 /BaseFont /Times-Roman >>\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT\n"
            "/F1 12 Tf\n");
    char *to_display=malloc(200);
    strcpy(to_display, "275 750 Td\n(");
	if(card.type==1)
		strcat(to_display, "Credit Card #");
	if(card.type==2)
		strcat(to_display, "Checking Card #");
	if(card.type==3)
		strcat(to_display, "Savings Card #");
	char *number=malloc(200);
	transform_integer_to_chars(number, card.id, 0);
	strcat(to_display, number);
	strcat(to_display, ") Tj\n");
	fprintf(pdfFile, "%s", to_display);
	
	/*strcpy(to_display, "Purpose: ");
	strcat(to_display, c.desc);
	fprintf(pdfFile, "%s", to_display);
	
	strcat(to_display, "\nBalance: ");
	transform_integer_to_chars(number, c.amount, 0);
	strcat(to_display, number);
	*/
	fprintf(pdfFile, "0 -24 Td\n(This is line 2) Tj\n");
	fprintf(pdfFile,
			"ET\n"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000010 00000 n \n"
            "0000000060 00000 n \n"
            "0000000121 00000 n \n"
            "0000000216 00000 n \n"
            "0000000297 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "397\n"
            "%%EOF\n");

    fclose(pdfFile);
}
#endif
