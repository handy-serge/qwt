# Update the DOM values from ClojureScript
This document describes how to use ClojureScript to change the text
displayed on the screen.

I will use the `Domina` library, the same as used for modern clojure
script tutorial.

## Create a table that we will change in HTML
First, we change our HTML page to contain the table, which will
represent our statistics display.

Modify the file `stats/resources/public/stats.html`:
```html
    <!doctype html>
    <html lang="en">
    <head>
        <meta charset="utf-8">
        <title>Statistics view page</title>
        <!--[if lt IE 9]>
        <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
        <![endif]-->
    </head>
    <body>
        <!-- pointing to cljsbuild generated js file -->
        <script src="js/stats.js"></script>

        <h1>Statistics display</h1>
        <p>This page displays statistical information. </p>

        <!-- Statics table -->
        <table border="1">
          <tr>
            <th>Gate</th>
            <th>Mean</th>
          </tr>
          <tr>
            <td>Gate 1</td>
            <td id="mean-for-gate-1">111.1</td>
          </tr>
          <tr>
            <td>Gate 2</td>
            <td id="mean-for-gate-2">222.2</td>
          </tr>
    </table>
    </body>
    </html>
```

If you load the `stats.html` in a browser, the page will contain the
table that look like this:

    | Gate   | Mean  |
    |--------|-------|
    | Gate 1 | 111.1 |
    | Gate 2 | 222.2 |

Our goal is to write the function that allows us to change the main
values to look like this:

    | Gate   | Mean  |
    |--------|-------|
    | Gate 1 | 555.5 |
    | Gate 2 | 777.7 |

## Use Domina to change DOM values.
To keep this simple, we added unique ID to every table value to be
able to address it: `mean-for-gate-1` and `mean-for-gate-2`.

Then we will add a ClojureScript file `src/cljs/stats/stats.cljs` That allows to change the value
of the given element:

```clojurescript
(ns experiment.stats.stats
  (:require [domina :as dom]))

(defn update! [id value]
  (-> id
    (dom/by-id)
    (dom/set-text! text)))
```

Now we can verify it works. Compile the project, run the server, and
then in browser repl type the following:

```cljs
(in-ns 'experiment.stats.stats)

(update! "mean-for-gate-1" 555.5)

(update! "mean-for-gate-2" 777.7)
;;=> #<[object HTMLTableCellElement]>
```

In a browser window we see that the value of the mean values is changed.

## Next step
So far, so good - we are able to change the page.

In a next step we will do some process improvements:

- We will add to our code documentation
- Statical code analysis
- More convenient REPL
