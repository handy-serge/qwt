(ns experiment.hello-world
  (:require [domina :as dom]
            [domina.css :as css]))


(defn update-text [text]
  (dom/set-text! (css/sel "#hello-world") text))

(defn a [i j]
  (/ 1 (+ (/ (* (+  ) (+ i j 1)) 2) i 1)))
