(IFS="|"
while read wrong_name name; do
  sed -i "s/|$wrong_name|/|$name|/g" repo-activity.txt
done < name_replacements.txt)

gource repo-activity.txt --hide dirnames,filenames --seconds-per-day 0.01 --auto-skip-seconds 1 -1280x720 --key
