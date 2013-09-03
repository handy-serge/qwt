(ns blacksmartie.client.stats.generate-csv
  "Outputs statistics data in CSV format."
  (:require [clojure.string :as string]
            [blacksmartie.client.stats.operations :refer [get-value
                                                             DataSourceType
                                                             ChannelLabel
                                                             StatisticParameter2D
                                                             StatisticParameter]]))

(defn generate-table-header []
  ["source"
   "id"
   "axis"

   "type"
   "channel"

   "mean"
   "median"
   "cv"

   "count-absolute"
   "count-percentage"
   "concentration"])

(defn generate-data-line [source id axis]
  [source
   id
   axis
   (get-value (DataSourceType. source id))
   (get-value (ChannelLabel. id axis))

   (get-value (StatisticParameter2D. source id "mean" axis))
   (get-value (StatisticParameter2D. source id "median" axis))
   (get-value (StatisticParameter2D. source id "cv" axis))

   (get-value (StatisticParameter. source id "count-absolute"))
   (get-value (StatisticParameter. source id "count-percentage"))
   (get-value (StatisticParameter. source id "concentration"))])

(defn generate-table
  "Generates statistical data in a form of table."
  []
  (doall (for [id [1 2 3 4]
               source ["plot" "gate"]
               axis ["x" "y"]]
           (generate-data-line source id axis))))

(def column-separator ";")
(def line-separator "\r\n")

(defn generate-csv-for-line [line]
  (string/join column-separator
               line))

(defn generate-csv-for-table [table header]
  (let [table-with-header (concat (conj '() header)
                                  table)]
    (string/join line-separator
                 (map generate-csv-for-line table-with-header))))

(defn generate-csv []
  (generate-csv-for-table (generate-table)
                          (generate-table-header)))
