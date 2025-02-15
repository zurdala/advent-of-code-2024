package main

import (
	"fmt"
	m "math"
	"slices"
)

func readInput() (l, r []int) {
	// read file input.txt and return 2 slices with the left and right columns
	l = []int{0}
	r = []int{0}

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
	for i := 0; i < len(distance); i++ {
		sum += distance[i]
	}

	fmt.Println("The total value is ", sum)

}
