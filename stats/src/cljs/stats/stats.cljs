(ns blacksmartie.client.stats
  "Updates statistics table.

  Statistics table displays the means and medians for the data displayed in gates and plots."
  (:require [domina :as dom]
            [domina.xpath :as xpath]
            [domina.css :as css]))

(defn data-source-type
  "Addresses the table cells that display the type of the data source.

  Parameters:

  - `data-source-type` One of #{:plot :gate}
  - `id` Id of the data source
  "
  [data-source-type id]
  (str "table.statistics"
       (format " tr[data-%s-id=\"%s\"]"
               (name data-source-type)
               id)
       (format " td[data-meaning=\"%s-type\"]"
               (name data-source-type))))

(defn set-value!
  "Sets the values for the given statistic table region."
  [selector value]
  (-> selector
      (css/sel)
      (dom/set-text! value)))

(defn test
  "Executes some functions in this file.

  Call this function from REPL to see how code behaves.
  "
  []
  (let  [first-id 1
         last-id 4
         data-source-types [:plot :gate]
         prefixes {:plot "PT-" :gate "gt-"}
         ids (range first-id
                    (inc last-id))
         label (fn [ds id]
                 (str (get prefixes ds "???" )
                      id))]

    ;; Sets all plot types to "PT-N", where N is plot id.
    ;; Sets all gate types to "gt-K", where K is gate id.
    (doseq [data-source data-source-types
            id ids]
      (print data-source id
             (label data-source id))
      (set-value! (data-source-type data-source id)
                    (label data-source id)))
      ;; Test ended...
      ))
