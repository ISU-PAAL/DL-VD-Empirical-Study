dir="$1"
[ -z "$dir" ] && dir="."

grep -e "easy score:" -e "normal score:" -e "hard score:" $(ls $dir/hardset_*.log | grep normalized) | sed -e 's@normalized_easiness@normalized-easiness@g' -e 's@correlation_factor@correlation-factor@g' -e 's@top_bottom_k@top-bottom-k@g' -e 's@random_@random-@g' -e 's@hardsets3/hardset_@@g' -e 's@testafter.log@testafter@g' -e 's@.log@,@g' -e 's@_@,@g' -e 's@ len@@g' -e 's@.log@@g' | sed -E 's@: ?@,@g'
