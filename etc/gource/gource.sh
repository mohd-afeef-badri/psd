cd ../.. && gource --output-custom-log ./etc/gource/repo-activity.txt && cd etc/gource

(IFS="|"
while read wrong_name name; do
  sed -i "s#|$wrong_name|#|$name|#g" repo-activity.txt
done < name_replacements.txt)

#gource --output-custom-log repo-activity.txt

#gource repo-activity.txt --hide dirnames,filenames --seconds-per-day 0.016 --auto-skip-seconds 1 -1280x720 --key --title '3 years of PSD solver' --logo ./../logo/logo_trans_10pct.png --font-size 30 --user-font-size 24 --highlight-users --file-filter '.*png*.' --file-filter '.*pdf*.'  --date-format "%b / %Y"  -o - | ffmpeg -y -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -preset ultrafast -pix_fmt yuv420p -crf 1 -threads 0 -bf 0 gource.mp4


gource repo-activity.txt --hide dirnames,filenames --seconds-per-day 0.016 --auto-skip-seconds 1 -1280x720 --key --title '3 years of PSD solver devlopment' --logo ./../logo/logo_trans_25pct.png --font-size 30 --user-font-size 24 --highlight-users --file-filter '.*png*.' --file-filter '.*pdf*.'  --date-format "%b / %Y"
