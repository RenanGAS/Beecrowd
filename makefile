FOLDER = 06-2023
FILE = ASP

all:
	rm -f ${FOLDER}/${FILE}
	g++ ${FOLDER}/${FILE}.cpp -o ${FOLDER}/${FILE}
	${FOLDER}/${FILE}