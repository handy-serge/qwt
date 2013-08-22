(ns blacksmartie.client.stats
  "Updates statistics table.

  Statistics table displays the means and medians for the data displayed in gates and plots."
  (:require-macros [hiccups.core :as hiccups])
  (:require [domina :as dom]
            [domina.css :as css]
            [hiccups.runtime :as hiccupsrt]
            ))

;;; ## Data access ##

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

(defn stat-by-axis
  "Addresses the cells that display particular statistic
  information that can be qualified by axis."
  [data-source-type id meaning axis]
  (str "table.statistics"
       (format " tr[data-%s-id=\"%s\"]"
               (name data-source-type)
               id)
       (format " td[data-meaning=\"%s\"][data-axis=\"%s\"]"
               (name meaning)
               (name axis))))

(defn stat
  "Addresses the cells that display particular statistic
  information."
  [data-source-type id meaning]
  (str "table.statistics"
       (format " tr[data-%s-id=\"%s\"]"
               (name data-source-type)
               id)
       (format " td[data-meaning=\"%s\"]"
               (name meaning))))

;; ## Operations ##
(defn set-value!
  "Sets the values for the given statistic table region."
  [selector value]
  (dom/set-text! (css/sel selector)
                 value))

;; ## HTML generation ##
(defn plot-label
  "Generates label for the plot."
  [plot-id]
  (format "Plot %s" plot-id))

(defn gate-label
  "Generates label for the gate."
  [gate-id]
  (format "G%s" gate-id))

(defn html-for-single-plot-counts-header-row
  "Plot header line for every plot header in counts table."
  [plot-id]
  (hiccups/html [:tr.plot-header
                 {:data-plot-id plot-id}
                 [:th (plot-label plot-id)]
                 [:td {:data-meaning :plot-type}]
                 [:td {:data-axis :x}]
                 [:td {:data-axis :y}]

                 ;; Last 4 columns are empty
                 (for [i (range 0 3)]
                   [:td])]))

(defn html-for-single-plot-counts-row
  [plot-id]
  (hiccups/html [:tr {:data-plot-id plot-id}
                 [:th (plot-label plot-id)]
                 [:td {:data-meaning :plot-type}]
                 [:td {:data-meaning :cv
                       :data-axis :x}]
                 [:td {:data-meaning :cv
                       :data-axis :y}]
                 [:td {:data-meaning :count-absolute}]
                 [:td {:data-meaning :count-percentage}]
                 [:td {:data-meaning :concentration}]]))

(defn html-for-single-gate-counts-row
  [gate-id]
  (hiccups/html [:tr {:data-gate-id gate-id}
                 [:th (gate-label gate-id)]
                 [:td {:data-meaning :gate-type}]
                 [:td {:data-meaning :cv
                       :data-axis :x}]
                 [:td {:data-meaning :cv
                       :data-axis :y}]
                 [:td {:data-meaning :count-absolute}]
                 [:td {:data-meaning :count-percentage}]
                 [:td {:data-meaning :concentration}]]))

(defn html-for-single-plot-counts
  "Generates HTML for 3 lines in a table that represents the counts of one plot:

  - Plot header
  - Plot counts
  - Gate counts
  "
  [plot-id]
  (str (html-for-single-plot-counts-header-row plot-id)
       (html-for-single-plot-counts-row plot-id)
       (html-for-single-gate-counts-row plot-id)))

(defn html-for-counts-table
  "Generates html for counts table"
  []
  (hiccups/html [:table {:id "counts-table"
                         :class "statistics"}
                 [:colgroup
                  (for [i (range 0 7)]
                    [:col])]

                 [:tr ;; Table header
                  [:th]
                  [:th "Type"]
                  [:th "CV (%)" [:br] "(X)"]
                  [:th "CV (%)" [:br] "(Y)"]
                  [:th "Count" [:br] "(#)"]
                  [:th "Count" [:br] "(%)"]
                  [:th "[C]" [:br] "(p/ul)"]]
                 (for [plot-id (range 1 5)]
                   (html-for-single-plot-counts plot-id))
                 ]))

(defn replace-html-for-counts-table!
  []
  (dom/swap-content! (dom/by-id "counts-table")
                     (html-for-counts-table)))


;;; ### HTML for stats ###
(defn html-for-single-plot-stats
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
    (hiccups/html
     [:tr.plot-header ;; Plot Header
      {:data-plot-id plot-id}
      [:th plot-label]
      [:td
       {:data-meaning :plot-type}]
      [:td
       {:data-axis :x}]
      [:td
       {:data-axis :y}]
      [:td
       {:data-axis :x}]
      [:td
       {:data-axis :y}]]
     [:tr ;; Plot Stats
      {:data-plot-id plot-id}
      [:th plot-label]
      [:td
       {:data-meaning :plot-type}]
      [:td {:data-meaning :mean
            :data-axis :x}]
      [:td {:data-meaning :mean
            :data-axis :y}]
      [:td {:data-meaning :median
            :data-axis :x}]
      [:td {:data-meaning :median
            :data-axis :y}]]
     [:tr ;; Gate Stats
      {:data-gate-id plot-id}
      [:th gate-label]
      [:td {:data-meaning :gate-type}]
      [:td {:data-meaning :mean
            :data-axis :x}]
      [:td {:data-meaning :mean
            :data-axis :y}]
      [:td {:data-meaning :median
            :data-axis :x}]
      [:td {:data-meaning :median
            :data-axis :y}]])))

(defn html-for-stats-table
  "Generates the table to display statistical information."
  []
  (let [first-plot-id 1
        last-plot-id 4]
    (hiccups/html
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
        (html-for-single-plot-stats plot)) ])))

(defn replace-html-for-stats-table!
  []
  (dom/swap-content! (dom/by-id "stats-table")
                     (html-for-stats-table)))


;;; The way I implement tabs is shamelessly stolen from:
;;; http://css-tricks.com/functional-css-tabs-revisited/
(defn html-for-stats-tab-panel
  "Generates HTML for tab panel that contains stats and counts tables."
  []
  (hiccups/html
   [:div.tabs
    [:div.tab
     [:input {:type :radio
              :id :tab-1
              :name :tab-group-1
              :checked true}]
     [:label {:for :tab-1}
      "Counts"]
     [:div.content
      [:table#counts-table]]]
    [:div.tab
     [:input {:type :radio
              :id :tab-2
              :name :tab-group-1}]
     [:label {:for :tab-2}
      "Stats"]
     [:div.content
      [:table#stats-table]]]]))

(defn replace-html-for-stats-tab-panel!
  []
  (dom/swap-content! (dom/by-id "stats-tab-panel")
                     (html-for-stats-tab-panel)))

;;; ## Initialization ##
(defn initialize! []
  (replace-html-for-stats-tab-panel!)
  (replace-html-for-counts-table!)
  (replace-html-for-stats-table!))

;;; ## Tests ##
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
