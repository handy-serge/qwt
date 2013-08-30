(ns stats.test.stats
  "Tests 'blacksmarie.client.stats' namespace"
  (:require [blacksmartie.client.stats :refer [set-value!
                                               data-source-type
                                               channel-label
                                               stat-by-axis
                                               stat
                                               initialize!]]))

(def data-source-types [:plot
                        :gate])
(def ids [1 2 3 4])
(def prefixes {:plot "PT-" :gate "gt-"})
(def axes [:x :y])
(def meanings-by-axis [:mean
                       :median
                       :cv])

(def meanings [:count-absolute
               :count-percentage
               :concentration
               :total-count])

(defn test-data-source-label
  "Verify that we label data sources properly.

   Sets all plot types to 'PT-N', where N is plot id.
   Sets all gate types to 'gt-K', where K is gate id."
  []
  (let [label-data-source (fn [ds id]
                            (str (get prefixes ds "???" ) id))]
    (doseq [data-source data-source-types
            id ids]
      (set-value! (data-source-type data-source id)
                  (label-data-source data-source id)))))

(defn test-channel-label
  "Test that we label channels correctly"
  []
  (let [label-channel (fn [plot-id axis]
                        (str "CH-" plot-id "-" (name axis)))]
      (doseq [plot-id ids
              axis axes]
        (set-value! (channel-label plot-id axis)
                    (label-channel plot-id axis)))))

(defn test-stats-by-axes
  "Test that we can access all stats properly."
  []
  (let [label-stat(fn [ds line-id meaning axis]
                     (str (get prefixes ds "???" )
                          line-id
                          ":" (name meaning)
                          ":" (name axis)))]

    ;; For some strange reason, I had a problem to run 4-level deep
    ;; do-seq inside defn in browser repl. So I manually unroll the
    ;; loop for axis to have the loop of only 3 levels deep.
    (doseq [ds data-source-types
            meaning meanings-by-axis
            id ids
            ]
      (set-value! (stat-by-axis ds id meaning :x)
                  (label-stat ds id meaning :x))
      (set-value! (stat-by-axis ds id meaning :y)
                  (label-stat ds id meaning :y)))))

(defn test-stats
  "Test that we can access all stats properly."
  []
  (let [label-stat(fn [ds line-id meaning]
                     (str (get prefixes ds "???" )
                          line-id
                          ":" (name meaning)))]

    (doseq [ds data-source-types
            meaning meanings
            id ids
            ]
      (set-value! (stat ds id meaning)
                  (label-stat ds id meaning)))))


(defn test
  "Executes some functions in this file.

  Call this function from REPL to see how code behaves.
  "
  []

  ;; Generate all needed html
  (initialize!)

  ;; Fill tables with test data
  ;; - stats table
  (test-data-source-label)
  (test-channel-label)
  (test-stats-by-axes)

  ;; - conuts table
  (test-stats)
  ;; Test ended...
  )
