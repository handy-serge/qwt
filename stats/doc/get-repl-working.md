# Create new project ready for REPL-driven development
This document contains some explanation about:

- What is the motivation and the purpose of this project
- How this project is created, where to put files
- How to use clojurescript REPL for quick development.

## Motivation

- Repl greatly speeds up development because you may see the changes
  quickly without need to build complete solution
- Repl allows for inspection of the running problem, greatly helping
  debug
- Repl allows to run code interactively in real environment, greatly
  improving profiling and performance optimisation


Sources of inspiration:

- [Modern ClojureScript](https://github.com/magomimmo/modern-cljs) -
  "official" ClojureScript tutorial talks about REPL by the tutorial
  2;
- [ClojureScriptOne](https://github.com/brentonashworth/one) - quite
  impressive demonstration of the ClojureScript application, built
  arond repl;
- [2012 State of Clojure survey](http://cemerick.com/2012/08/06/results-of-the-2012-state-of-clojure-survey/) -
  REPL is considered is the #2 "biggest win in using clojure".
  (Functional programming


More specifically, for ClojureScript, as stated by the
[ClojureScript workflow discussion](https://github.com/brentonashworth/one/wiki/Workflow#workflow):

    > When working with ClojureScript, having a good workflow is
    > essential. The first thing to know about workflow is that you should
    > be working from the REPL as much as possible. In fact, if you are
    > not spending most of your time in the REPL, you're doing it wrong.
    >
    > Using the REPL as the main way to deliver code to the browser means
    > never having to refresh the page. One could theoretically build an
    > entire application without a single page refresh. If you find
    > yourself refreshing the page after every change you make, you're
    > doing it wrong.






