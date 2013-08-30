(ns blacksmartie.client.stats.generate-html
  "Generates HTML that represents the statistics table panel."
  (:require-macros [hiccups.core :as hiccups])
  (:require [hiccups.runtime :as hiccupsrt]
            [domina :as dom]))

;; ## HTML generation ##
(defn plot-label
  "Generates label for the plot."
  [plot-id]
  (format "Plot %s" plot-id))

(def plot-total-label
  "Label displayed for plot statistics"
  "All")

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
                 [:th plot-total-label]
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
                  [:th "CV(%)" [:br] "(X)"]
                  [:th "CV(%)" [:br] "(Y)"]
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
      [:th plot-total-label]
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


;;; ### HTML for statistics tabs panel
;;; The way I implement tabs is shamelessly stolen from:
;;; http://css-tricks.com/functional-css-tabs-revisited/
(defn html-for-stats-tab-panel
  "Generates HTML for tab panel that contains stats and counts tables."
  []
  (hiccups/html
   [:div#stats-tab-panel.statistics.tab_panel
    [:button#save-as-csv.statistics.tab_panel_button {:role :button}
     "Save table as .csv"]

    [:div.statistics.single_tab
     [:input {:type :radio
              :id :tab-1
              :name :tab-group-1
              :checked true}]
     [:label {:for :tab-1}
      "Counts"]
     [:div.statistics.tab_content
      [:table#counts-table.statistics]]]
    [:div.statistics.single_tab
     [:input {:type :radio
              :id :tab-2
              :name :tab-group-1}]
     [:label {:for :tab-2}
      "Stats"]
     [:div.statistics.tab_content
      [:table#stats-table.statistics]]]]))

(defn replace-html-for-stats-tab-panel!
  []
  (dom/swap-content! (dom/by-id "stats-tab-panel")
                     (html-for-stats-tab-panel)))


(defn generate-html!
  "Generates html for statistic table display"
  []
  (replace-html-for-stats-tab-panel!)
  (replace-html-for-counts-table!)
  (replace-html-for-stats-table!))
