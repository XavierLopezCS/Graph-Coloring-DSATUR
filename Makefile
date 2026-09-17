SRC=src

exercise_1.out:
	@ mkdir -p bin
	g++ $(SRC)/exercise_1.cpp -o bin/exercise_1

clean:
	rm -r bin

test: exercise_1.out 
	bash test.sh exercise_1 "" ""
