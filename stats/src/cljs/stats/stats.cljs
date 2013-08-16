(ns blacksmartie.client.stats
  "Updates statistics table.

  Statistics table displays the means and medians for the data displayed in gates and plots."
  (:require [domina :as dom]
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

(defn channel-label
  "Addresses the cells that display the channel label for the given axis"
  [plot-id axis]
  (str "table.statistics"
       (format " tr.plot-header[data-plot-id=\"%s\"]"
               plot-id)
       (format " td[data-axis=\"%s\"]"
               (name axis))))

(defn stat
  "Addresses the cells that display particular statistic information"
  [data-source-type id meaning axis]
  (str "table.statistics"
       (format " tr[data-%s-id=\"%s\"]"
               (name data-source-type)
               id)
       (format " td[data-meaning=\"%s\"][data-axis=\"%s\"]"
               (name meaning)
               (name axis))))

(defn set-value!
  "Sets the values for the given statistic table region."
  [selector value]
  (dom/set-text! (css/sel selector)
                 value))


(defn test
  "Executes some functions in this file.

  Call this function from REPL to see how code behaves.
  "
  []
  (let  [data-source-types [:plot :gate]
         prefixes {:plot "PT-" :gate "gt-"}
         ids [1 2 3 4]
         axes [:x :y]
         meanings [:mean :median]
         label-data-source (fn [ds id]
                             (str (get prefixes ds "???" ) id))
         label-channel (fn [plot-id axis]
                         (str "CH-" plot-id "-" (name axis)))
         label-stat (fn [ds id meaning axis]
                      (str (get prefixes ds "???" )
                           id
                           ":" (name meaning)
                           ":" (name axis)))]

    ;; Sets all plot types to "PT-N", where N is plot id.
    ;; Sets all gate types to "gt-K", where K is gate id.
    (doseq [data-source data-source-types
            id ids]
      (set-value! (data-source-type data-source id)
                    (label-data-source data-source id)))

    ;; Set all channel labels
    (doseq [plot-id ids
            axis axes]
      (set-value! (channel-label plot-id axis)
                  (label-channel plot-id axis)))

    ;; Set all stats
    (doseq [ds data-source-types
            id ids
            meaning meanings
            axis axes]
      (set-value! (stat ds id meaning axis)
                  (label-stat ds id meaning axis)))
      ;; Test ended...
      ))
