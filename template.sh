#! /bin/sh

# outputs a code snippet to be added to the setup script for a given program's config directory
# it must be run in dots directory
# it won't work completely for most config files but it gets rid of some typing of boilerplate
# don't forget to also add "setup_whatever" to the setup_all() function in the setup script

# e.g. ./template.sh foot ~/.config/foot
# will output a snippet that would  symlink every file in $DOTS/foot under $HOME/.config/foot
# any occurrence "$HOME" expansion (i.e. /home/your-username) in $2 is replaced with '$HOME'
# if the second argument is omitted, $HOME/.config/"$1" is selected

[ -z "$1" ] &&  exit 1
dir="${1%%/*}"

if [ -z "$2" ]; then
    target="\$config_dir/$1"
elif [ "$2" = "${2#$HOME}" ]; then
    target="$2"
else
    target=\$HOME"${2#$HOME}"
fi

printf "setup_%s() {\n" "$dir"
# do for loop for directories as well?
printf "    %s %s %s\n" "mkdir" "-pv" "\"$target\""

find "$dir" -type f | while read -r file; do
    printf "    %s %s %s %s\n" "ln" "-sfv" "\"\$dots/$file\"" "\"$(dirname -- "$target")/$file\""
done

printf "}\n\n"
