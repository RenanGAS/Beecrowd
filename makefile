FOLDER = 04-2023
FILE = boss

all:
	rm -f ${FOLDER}/${FILE}
	g++ ${FOLDER}/${FILE}.cpp -o ${FOLDER}/${FILE}
	${FOLDER}/${FILE}