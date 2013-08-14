(ns experiment.stats.stats
  "Updates statistics table.

  Statistics table displays the means and medians for the data displayed in gates and plots."
  (:require [domina :as dom]
            [domina.xpath :as xpath]
            [domina.css :as css]))


(defn select-plot-type
  "Returns CSS selector that addresses the table cells that display plot type."
  [plot-id]
  (str "table.statistics"
       (format " tr[data-plot-id=\"%s\"]" plot-id)
       " td[data-meaning=\"plot-type\"]"))


(defn set-plot-type!
  "Updates the cell that displays the plot type for the given plot.

   Parameters:

   - plot-id: ([1..4], int) What plot type to update
   - plot-type: (string) what to display as a plot type

   Example of usage:

       (set-plot-type! 1 'S')
       ;;=> will display 'S' in the type cell for plot 1.
   "
  [plot-id plot-type]
  (-> plot-id
      (select-plot-type)
      (css/sel)
      (dom/set-text! plot-type)))


(defn test
  "Executes some functions in this file.

  Call this function from REPL to see how code behaves.
  "
  []
  ;; Sets the type of the first plot to "Z"
  (set-plot-type! 1 "Z")

  ;; The type of the third plot should become "L"
  (set-plot-type! 3 "L"))
