package main

// https://adventofcode.com/2024/day/1

import (
	"bufio"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

func check(e error) {
	if e != nil {
		log.Fatalln(e)
	}
}

// there is a missing abs function for ints in the stdlib
// or at least, I haven't found it
func absInt(i int) int {
	if i < 0 {
		i = -i
	}
	return i
}

func readLines(fname string) (lines []string) {
	log.Println("Reading lines of ", fname)
	inputFile, err := os.Open("input.txt")
	check(err)

	fileScanner := bufio.NewScanner(inputFile)
	fileScanner.Split(bufio.ScanLines)

	for fileScanner.Scan() {
		lines = append(lines, fileScanner.Text())
	}
	return
}

func readInput() (left_column, right_column []int) {
	// read file input.txt and return 2 slices with the left and right columns
	left_column = make([]int, 0)
	right_column = make([]int, 0)

	for _, line := range readLines("input.txt") {
		// strings.Fields parses the string and returns a slice
		// containing all elements between whitespaces/tabs/etc
		fields := strings.Fields(line)

		// converts string to int
		l, err := strconv.Atoi(fields[0])
		check(err)
		r, err := strconv.Atoi(fields[1])
		check(err)

		// append returns a new slice
		left_column = append(left_column, l)
		right_column = append(right_column, r)
	}

	return
}

func main() {
	log.Println("hello world")

	left, right := readInput()

	slices.Sort(left)
	slices.Sort(right)

	var distance []int

	for i := 0; i < len(left); i++ {
		distance = append(distance, absInt(left[i]-right[i]))
	}

	sum := 0
	for _, d := range distance {
		sum += d
	}

	log.Println("The total value is ", sum) // result: 2285373

}
