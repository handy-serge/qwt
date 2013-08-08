(ns experiment.stats.stats
  (:require [domina :as dom]))

(defn update! [id text]
  (-> id
    (dom/by-id)
    (dom/set-text! text)))
