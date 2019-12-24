package main

import (
	"fmt"
	"time"
)

func main() {
	go count("sheep")
	count("fish")

	channel()

	//select_channel()

	jobs := make(chan int, 100)
	results := make(chan int, 100)

	go worker(jobs, results)
	go worker(jobs, results)
	go worker(jobs, results)

	for i := 0; i < 100; i++ {
		jobs <- i
	}

	close(jobs)

	for j := 0; j < 100; j++ {
		fmt.Println(<-results)
	}


}

func count(thing string) {
	for i :=1; i <= 10; i++ {
		fmt.Println(i, thing)
		time.Sleep(time.Millisecond * 500)
	}
}

func channel() {
	c := make(chan string)
	go count_c("lion", c)

//	for {
//		msg, open := <- c
//		if (!open) {
//			break;
//		}
	for msg := range c{
		fmt.Println(msg)
	}
}

func count_c(thing string, c chan string) {
	for i := 1; i <= 10; i++ {
		c <- thing
		time.Sleep(time.Millisecond * 500)
	}

	close(c)
}

func select_channel() {
	c1 := make(chan string)
	c2 := make(chan string)

	go func() {
		for {
			c1 <- "Every 500ms"
			time.Sleep(time.Millisecond * 500)
		}
	}()

	go func() {
		for {
			c2 <- "Every two seconds"
			time.Sleep(time.Second * 2)
		}
	}()

	for {
		select {
		case msg1 := <- c1:
			fmt.Println(msg1)
		case msg2 := <- c2:
			fmt.Println(msg2)
		}
	}
}

func worker(jobs <-chan int, results chan<- int) {
	for n := range jobs {
		results <- fib(n)
	}
}

func fib(n int) int {
	if n <=1 {
		return n
	}

	return fib(n-1) + fib(n-2)
}
