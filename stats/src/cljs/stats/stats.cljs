(ns blacksmartie.client.stats
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

(defn select-gate-type
  "Returns CSS selector that addresses the table cells that display gate type."
  [gate-id]
  (str "table.statistics"
       (format " tr[data-gate-id=\"%s\"]" gate-id)
       " td[data-meaning=\"gate-type\"]"))

(defn set-value!
  "Sets statistics value."
  [selector value]
  (-> selector
      (css/sel)
      (dom/set-text! value)))

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
  (set-value! (select-plot-type plot-id)
              plot-type))


(defn set-gate-type!
  "Updates the cell that displays the gate type for the given gate.

   Parameters:

   - gate-id: ([1..4], int) What gate type to update
   - gate-type: (string) what to display as a gate type

   Example of usage:

       (set-gate-type! 1 'S')
       ;;=> will display 'S' in the type cell for gate 1.
   "
  [gate-id gate-type]
  (set-value! (select-gate-type gate-id)
              gate-type))


(defn test
  "Executes some functions in this file.

  Call this function from REPL to see how code behaves.
  "
  []
  (let  [first-id 1
         last-id 4
         ids (range first-id
                    (inc last-id))]

      ;; Sets all gate types to "GT-N", where N is gate id.

    (doseq [gate-id ids]
      (set-gate-type! gate-id (str "GT-" gate-id)))

      ;; Sets all gate types to "PT-N", where N is plot id.

    (doseq [plot-id ids]
      (set-plot-type! plot-id (str "PT-" plot-id)))

      ;; Test ended...
      ))
