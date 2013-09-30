# Introduction to js-experiment

## How to launch web server?
1- term1> cd ~/work/sandbox/js-experiment
2- term1> lein ring server

## How to launch nRepl in emacs?
1- From Emacs, alt-x --> nrepl-jack-in
2- From nRepl --> (brower-repl)
3- From nrepl> (in-ns 'experiment.big-array)

## How to compile?
term2> lein cljsbuild once


## How to see results?
1- Open a browser (i.e Chrome for instance)
2- Type following url: http://localhost:3000/big-array.html


## Description of benchmarks
1- src/cljs/big-array/main.cljs
...bench-array-creation(arg1, arg2)
...Description:
......Allocate a Javascript array according the number of events and number of bytes per event.
......The execution time is measured with the clojure.core/time function.
...Arguments:
......arg1 is the number of events to allocate, and
......arg2 is the number of bytes per events to allocate
...Return:
......A string corresponding to the time elapsed during execution of the function.


2- src/cljs/big-array/main.cljs:
...bench-array-addition(arg1, arg2)
...Description:
......Allocate a Javascript array according the number of events and number of bytes per event.
......Then modify each event defined in the array (we basically increment each integer of the event)
......The execution time is measured with the clojure.core/time function.
......Only the execution time of modifications are measured.
...Arguments:
......arg1 is the number of events to allocate, and
......arg2 is the number of bytes per events to allocate
...Return:
......A string corresponding to the time elapsed during execution of the function.