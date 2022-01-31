(IFS="|"
while read wrong_name name; do
  sed -i "s/|$wrong_name|/|$name|/g" repo-activity.txt
done < name_replacements.txt)

gource repo-activity.txt --hide dirnames,filenames --seconds-per-day 0.02 --auto-skip-seconds 1 -1280x720 --key --title '3 years of PSD solver devlopment' --logo ./Logo/logo_trans_25pct.png
