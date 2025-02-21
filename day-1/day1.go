package main

// https://adventofcode.com/2024/day/1

import (
	"bufio"
	"fmt"
	m "math"
	"os"
	"slices"
	"strconv"
	"strings"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func readInput() (left_column, right_column []int) {
	// read file input.txt and return 2 slices with the left and right columns
	left_column = make([]int, 0)
	right_column = make([]int, 0)

	inputFile, err := os.Open("input.txt")
	check(err)

	fileScanner := bufio.NewScanner(inputFile)
	fileScanner.Split(bufio.ScanLines)

	for fileScanner.Scan() {
		line := fileScanner.Text()
		fields := strings.Fields(line)
		l, err := strconv.Atoi(fields[0])
		check(err)
		r, err := strconv.Atoi(fields[1])
		check(err)
		left_column = append(left_column, l)
		right_column = append(right_column, r)
	}

	return
}

func main() {
	fmt.Println("hello world")

	left := []int{3, 4, 2, 1, 3, 3}
	right := []int{4, 3, 5, 3, 9, 3}

	left, right = readInput()

	slices.Sort(left)
	slices.Sort(right)

	var distance []int

	for i := 0; i < len(left); i++ {
		distance = append(distance, int(m.Abs(float64(left[i]-right[i]))))
	}

	fmt.Println(distance)

	sum := 0
	for i := range len(distance) {
		sum += distance[i]
	}

	fmt.Println("The total value is ", sum) // result: 2285373

}
