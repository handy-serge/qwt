(ns webcanter.data
  "Explore what kind of data manipulations are available in Incanter.

  See also:
  - http://liebke.github.io/incanter/index.html
  - http://incanter.org/docs/data-sorcery-light-new.pdf
  - https://github.com/liebke/incanter/wiki/datasets

  This file contains some functions that demonstrate incanter API.
  Try them in REPL to see what is possible.
  "
  (:require [incanter.core
             :as incanter
             :refer [col-names ; See dataset column names
                     view ; See things
                     $ ; Select columns and rows
                     $rollup ; Total calculations
                     $order ; Sort data
                     dataset ; Create dataset from clojure structure.
                     with-data ; Macro to attach many operations to
                               ; the same dataset.
                     conj-rows ; Concatenate together several datasets
                     ]]
            [incanter.charts :as charts :refer [scatter-plot]]
            [incanter.datasets :as datasets :refer [get-dataset]]))

;;;

(def iris (get-dataset :iris))
(def us-arrests (get-dataset :us-arrests))
(def chick-weight (get-dataset :chick-weight))
(def survey (get-dataset :survey))

(def cytometry (dataset [:x :y]
                        [[1 1]
                         [1 1]
                         [1 2]
                         [6 1]
                         [6 1]
                         [6 1]
                         [6 1]
                         [6 1]
                         [5 4]]))

(defn random-data
  "Generate random dataset"
  [size]
  (take size
        (for [_ (range size)
              :let [x (rand-int 10000)
                    y (rand-int  10000)]]
          [x y])))

(defn random-dataset
  "Dataset with the random data."
  [size]
  (dataset [:x :y]
           (random-data size)))


(def r100
  "Random dataset with 100 lines"
  (random-dataset 100))

(def r-kilo
  "Random dataset with 1000 lines"
  (random-dataset 1000))

(def r-kilo-10
  "Random dataset with 10000 lines"
  (random-dataset 10000))

(def r-kilo-100
  "Random dataset with 100000 lines"
  (random-dataset 100000))

(def r-kilo-540
  "Random dataset with 540000 lines"
  (random-dataset 540000))

(def r-mega
  "Random dataset with 1000000 lines"
  (random-dataset 1000000))

(defn count-same-place-points
  "Takes dataset with 2 columns `:x` and `:y` and returns
   dataset that adds third column `:points-count` with the number of
    points on every coordinate."
  [data]
  ($rollup :count :points-count [:x :y] data))


(defn combine-many-random-datasets
  "Sytnthetic database of many points"
  []
  ;; Merge together many datasets.
  (conj-rows r-kilo-100 r-kilo-100 r-kilo-100
             r-kilo r-kilo r-kilo r-kilo r-kilo r-kilo r-kilo r-kilo
             r100 r100 r100 r100 r100 r100 r100 r100 r100 r100 r100 r100 r100))

(def r-combined
  "Combines several random datasets together"
  (combine-many-random-datasets))

(defn count-rows
  "Returns the number of the rows in dataset. "
  [dataset]
  (count (:rows dataset)))

(defn scatter-plot-of-counts
  "Returns the scatter plot that groups together the points at the same place and shows them as colors."
  [dataset]
  (scatter-plot :x :y
                :group-by :points-count
                :data (count-same-place-points dataset)))
