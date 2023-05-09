FOLDER = 05-2023
FILE = makePairs

all:
	rm -f ${FOLDER}/${FILE}
	g++ ${FOLDER}/${FILE}.cpp -o ${FOLDER}/${FILE}
	${FOLDER}/${FILE}