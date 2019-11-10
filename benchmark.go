package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"time"
)

func main() {
	start := time.Now()

	var i int
	fhout, err := os.Create("result.txt")
	if err != nil {
		log.Panicln(err.Error())
	}
	defer fhout.Close()
	bufout := bufio.NewWriter(fhout)

	fhin, err := os.Open("random_numbers.txt")
	if err != nil {
		log.Panicln(err.Error())
	}
	defer fhin.Close()

	var t1, t2, t3 float64
	var line string
	var xxx []string
	scanner := bufio.NewScanner(fhin)
	for scanner.Scan() {
		line = scanner.Text()
		xxx = strings.Split(line, "\t")
		if len(xxx) != 3 {
			log.Panicln("expecting 3 floats but got: ", xxx)
		}
		t1, err = strconv.ParseFloat(xxx[0], 64)
		if err != nil {
			log.Panicln(err.Error())
		}
		t2, err = strconv.ParseFloat(xxx[1], 64)
		if err != nil {
			log.Panicln(err.Error())
		}
		t3, err = strconv.ParseFloat(xxx[2], 64)
		if err != nil {
			log.Panicln(err.Error())
		}
		result := t1 / t2
		if result != t3 {
			// print err
		}

		bufout.WriteString(fmt.Sprintf("%f\t%f\t%f\n", t1, t2, result))
		i++
		/*if i > 1000000 {
			break
		}*/
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	stop := time.Now()
	fmt.Printf("processed %d lines in %+v\n", i, stop.Sub(start))
}
