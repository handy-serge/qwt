# Housekeeping
This document describes how to setup some additional tools for better
development practices.

## Better REPL
Using browser repl from terminal is not very convenient:

- There are no history
- Editing of the code is clumsy
- It is cumbersome constantly to switch between REPL and editor

The solution is to use the to use [Piggieback library][1].

So, we add the dependency in `project.clj`:

```clojure
(defproject
  ...
  ...

  :dependencies [...
                 [;; Use ClojureScript browser REPL from nREPL
                 com.cemerick/piggieback "0.0.5"]
                 ...]
  :repl-options {:nrepl-middleware [;; Make nREPL use Piggieback
                                    cemerick.piggieback/wrap-cljs-repl]}

  :injections [(require '[cljs.repl.browser :as brepl]
                        '[cemerick.piggieback :as pb])
               (defn browser-repl
                   "Start server component of the ClojureScript browser REPL"
                   []
                 (pb/cljs-repl :repl-env
                               (doto (brepl/repl-env :port 9000)
                                     cljs.repl/-setup)))]
  ...)

```

So, it is the time to check if it works, fire up emacs!


## How to use browser REPL from emacs
With a new shiny tool, we can implement couple of new functions
that can update data in a statistics table, and call them from the
REPL to see if they work:

```clojurescript
(ns experiment.stats.stats
  (:require [domina :as dom]))

(defn update! [id text]
  (-> id
    (dom/by-id)
    (dom/set-text! text)))

(defn color! [id color]
  (-> id
      (dom/by-id)
      (dom/set-styles! {:color color})))

(defn update-means! [mean-1 mean-2]
  (map update!
       ["mean-for-gate-1" "mean-for-gate-2"]
       [mean-1 mean-2]))
```


This is how to drive the browser from Emacs:

- Start the server with `lein ring server-headless`
- Open the file `src/cljs/stats/stats.cljs` in emacs with nREPL
  configured.
- Do `M-x nrepl-jack-in` in emacs
- In the `*nrepl*` buffer, type `(browser-repl)`
- Reload `stats.html` page in a browser

Congratulations - now you can execute any part of ClojureScript code
directly from Emacs. Usual features work:

- `C-c C-l` - to reload the file
- `C-c C-c` - to execute expressions
- etc...

So, you may try something like this:

```clojurescript
(in-ns 'experiment.stats.stats)

;;=> experiment.stats.stats

(update-means! 33 44)
;;=> #<object HTMLTableCellElement]>

;; (Check browser that now the 'Mean' column of the statistics table
;; have 33 and 44.
```

## Static code analysis
I add two plugins for code checking:

- [Kibit: static code analyzer for Clojure][2]
- [Bikeshed: to tell you your code is bad][3]

## Documentation generation
I added
[Marginalia (light-weight literate programming tool) to the project.][4]

## Setting up aliases
I needed to define couple of
[Leiningen aliases (search for `:aliases`)][5], because of 2 reasons:

- I want to run `kibit` and `bikeshed` commands in a one command
- I want to pass some command-line parameters to `lein marg`

Thus, 2 aliases were defined:

- `lein @doc` will generate documentation
- `lein @check` will perform static code checking

## Project file cleanup
I put all developer dependencies under `:profiles` section of the
`project.clj` file.

Then I put profiles into separate file `profiles.clj`.

So, now the file `project.clj` contains only core stuff that
absolutely needed to have project run in production. And
`profiles.clj` holds the rest of the picture: plumbing, development
tools, implementation details.




[1]: https://github.com/cemerick/piggieback "Piggieback:
 run clojurescript REPL from nREPL"

[2]: https://github.com/jonase/kibit "Kibit: static code analyzer for Clojure."
[3]: https://github.com/dakrone/lein-bikeshed "Bikeshed: tell you if your code is bad."
[4]: https://github.com/fogus/marginalia "Marginalia: lightweight literate programming for Clojure"

[5]: https://github.com/technomancy/leiningen/blob/master/sample.project.clj "
Sample leiningen project. (Look for `:aliases`)."







