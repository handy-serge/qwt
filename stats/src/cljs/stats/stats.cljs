(ns experiment.stats.stats
  (:require [domina :as dom]))

(defn update! [id text]
  (-> id
    (dom/by-id)
    (dom/set-text! text)))

(defn color! [id color]
  (-> id
      (dom/by-id)
      (dom/set-styles! {:color color})))

(defn update-means! [mean-1 mean-2]
  (map update!
       ["mean-for-gate-1" "mean-for-gate-2"]
       [mean-1 mean-2]))
