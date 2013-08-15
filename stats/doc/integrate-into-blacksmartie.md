# Integrate the code from experiment project in Blacksmartie
So far, we achieved the great progress in implementing our statistics
view. But how will it look inside of the real application? In this
document I describe how to put the code from this project into
blacksmartie.

## Make code build as a part of blacsmartie
Initially I set up the statistics display as a separate project,
because it was difficult for me to get browser REPL working.
Browser REPL allowed me to evaluate my code quickly and produce
something interesting. How do I get it back to the blacksmartie?

I decided to not create separate branch or repository for my
experiments, because I see them small - develop something, integrate
it to the production, and remove them. At the same time I want the
experimental work being commit to source control and reviewed as a
part of usual development workflow. So, when some pieces are done - I
will just copy neccessary files into the main project and main them
run.

Thus, this is what is needed to get statistics table into blacsmartie:

- Copy source files:
    - Copy `blacksmartie/experiment/stats/src/cljs/stats/stats.cljs`
      -> `blacksmartie/src/blacksmartie/client/stats.cljs`
    - Copy
      `blacksmartie/experiment/stats/resources/public/css/stats.css`
      -> `blacksmartie/resources/public/css/stats.css`
- Adjust the namespace for `stats.cljs` file into
  `blacksmartie.client.stats`
- Add `Domina`as dependendency to the `project.clj` file.

That is it, now we can run `lein cljsbuild once` from the root of the
blacksmartie project and check that `blacsmartie.client.stats` is
present in a generated JavaScript file.

## Generate HTML dynamically with Hiccup
Our experimental stats project was using static hand-written
`stats.html` file to define the statistics table. Blacksmartie
generates the HTML page on a server side, using Hiccup library.

Thus, we add generation of the HTML for stats table into the file
`blacksmartie/src/blacksmartie/views/experiment.clj`:

```clojure

;; ...

(defn plot-stats
  "Generates HTML for  3 lines in a table
   that represent the statistics for one plot:

   - Plot header
   - Plot stats
   - Gate stats

  Parameters:

  - plot-id Id of the plots - integers from 1 to 4.
  "
  [plot-id]
  (let [plot-label (format "Plot %s" plot-id)
        gate-label (format "G%s" plot-id)]
    (html
     [:tr.plot-header ;; Plot Header
      {:data-plot-id plot-id}
      [:th plot-label]
      [:td
       {:data-meaning :plot-type} "S"]
      [:td "FSC"]
      [:td "SSC"]
      [:td "FSC"]
      [:td "SSC"]]
     [:tr ;; Plot Stats
      {:data-plot-id plot-id}
      [:th plot-label]
      [:td
       {:data-meaning :plot-type} "S"]
      [:td "11.1"]
      [:td "22.2"]
      [:td "33.3"]
      [:td "44.4"]]
     [:tr ;; Gate Stats
      [:th gate-label]
      [:td "R"]
      [:td "55.5"]
      [:td "66.6"]
      [:td "77.7"]
      [:td "88.8"]])))

(defn stats
  "Generates the table to display statistical information."
  []
  (html
   (include-css "/css/stats.css")
   [:table.statistics
    [:colgroup [:col] [:col] [:col] [:col] [:col] [:col]]
    [:tr ;; Table header
     [:th]
     [:th "Type"]
     [:th "Mean" [:br] "(X)"]
     [:th "Mean" [:br] "(Y)"]
     [:th "Med" [:br] "(X)"]
     [:th "Med" [:br] "(Y)"]]
    (for [plot (range 1 5)]
      (plot-stats plot)) ]))

(defn stats
  "Generates the table to display statistical information."
  []
  (let [firs-plot-id 1
        last-plot-id 4] )
  (html
   (include-css "/css/stats.css")
   [:table.statistics
    [:colgroup [:col] [:col] [:col] [:col] [:col] [:col]]
    [:tr ;; Table header
     [:th]
     [:th "Type"]
     [:th "Mean" [:br] "(X)"]
     [:th "Mean" [:br] "(Y)"]
     [:th "Med" [:br] "(X)"]
     [:th "Med" [:br] "(Y)"]]
    (for [plot (range first-plot-id
                      (inc last-plot-id))]
      (plot-stats plot)) ]))

(defn experiment []
  (html
   (include-css "/css/experiment.css")
   [:div#control-panel
    (controls)
    (compensations)
    (pmts-config)
    (stats) ; <= We display our table here, below PMT config..
    ]))
```

That is it. Now we build blacksmartie and see our statiscs table
displayed as it should on experiment page.

Then we can open the Firebug or Chrome developer tools, and open
JavaScript console. Chrome is nicely gives the autocompletion in the
console. Console in Chrome is invoked by the `Ctrl-Shift-J`. Then
type:

```javascript
blacksmartie.client.stats.set_plot_type_BANG_(1, "Z")
```

Here we go, statistic table nicely integrated!

## Next steps
In the next step we implement the rest of functionality needed to
display the rest of statistical data.
