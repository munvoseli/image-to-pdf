#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TEX_FILE "impd.tex"

#define MODE(X) "\033[" X "m"

const char* BEGIN =
"\\documentclass{article}\n"
"\\nonstopmode\n"
"\\usepackage[paperwidth=20cm,paperheight=575cm]{geometry}\n"
"\\usepackage{graphicx}\n"
"\\geometry{margin=0cm}\n"
"\\setlength{\\parindent}{0pt}\n"
"\\setlength{\\parskip}{0pt}\n"
"\\pagestyle{empty}\n"
"\\AddToHook{shipout/before}{\\pdfpageheight=\\pagetotal}\n"
"\\begin{document}\n";

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Usage: ./a.out \"author name\" 1.jpeg 2.jpeg\n");
		return 1;
	}
	FILE* fp = fopen(TEX_FILE, "w");
	//fwrite(BEGIN, 1, sizeof(BEGIN), fp);
	fprintf(fp, BEGIN);
	fprintf(fp, "%s\n\n", argv[1]);
	for (int i = 2; i < argc; ++i) {
		fprintf(fp, "\\includegraphics[width=\\textwidth]{%s}", argv[i]);
		fprintf(fp, "\n\\pagebreak\n");
	}
	fprintf(fp, "\\end{document}\n");
	fclose(fp);
	pid_t pid = fork();
	if (pid == 0) { // child
		execlp("pdflatex", "pdflatex", TEX_FILE, NULL);
	} else {
		int wstatus;
		waitpid(pid, &wstatus, 0);
	}
	printf(MODE("32;1") "Success" MODE("0") "\n");
	return 0;
}
