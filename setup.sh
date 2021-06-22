#! /bin/sh

config_dir="${XDG_CONFIG_HOME:-$HOME/.config}"
cache_dir="${XDG_CACHE_HOME:-$HOME/.cache}"
data_dir="${XDG_DATA_HOME:-$HOME/.local/share}"

bin="$HOME/bin"
lbry="${LBRY:-$HOME/library}"
dots="${DOTS:-$lbry/projects/dots}"

setup_all() {
    setup_general
    setup_bspwm
    setup_dunst
    setup_foot
    setup_git
    setup_kanshi
    setup_logiops
    setup_mako
    setup_mpv
    setup_picom
    setup_polybar
    setup_river
    setup_rofi
    setup_spotifyd
    setup_st
    setup_sxhkd
    setup_udevmon
    setup_vim
    setup_x
    setup_zathura
    setup_zsh
}

setup_general() {

    # user-dirs.dirs
    XDG_DESKTOP_DIR="$HOME/useless/desktop"
    XDG_DOWNLOAD_DIR="$HOME/library/tmp/downloads"
    XDG_TEMPLATES_DIR="$HOME/useless/templates"
    XDG_PUBLICSHARE_DIR="$HOME/useless/public"
    XDG_DOCUMENTS_DIR="$HOME/library/documents"
    XDG_MUSIC_DIR="$HOME/library/media/audio/music"
    XDG_PICTURES_DIR="$HOME/library/media/images"
    XDG_VIDEOS_DIR="$HOME/library/media/video"

    for d in DESKTOP DOWNLOAD TEMPLATES PUBLICSHARE DOCUMENTS MUSIC PICTURES VIDEOS; do
        eval "dir=\$XDG_${d}_DIR"
        xdg-user-dirs-update --set $d "$dir"
    done

    xdg-user-dirs-update

    # the following plus some lines in zshenv are for clearing up the home directory

    if command -v bat >/dev/null 2>&1; then
        bat_dir="$(bat --config-file)"
        mkdir -p "$(dirname -- "$bat_dir")"
        echo '--theme="gruvbox-dark"' > "$(bat --config-file)"
    fi

    mkdir -p "$data_dir/tig"

    if [ "$WGETRC" ]; then
        echo hsts-file \= "$cache_dir"/wget-hsts > "$config_dir/wgetrc"
    fi
}

setup_bspwm() {
    mkdir -pv "$config_dir/bspwm" "$config_dir/autorandr" "$bin"

    ln -sfv "$dots/bspwm/bspwmrc" "$config_dir/bspwm/bspwmrc"
    ln -sfv "$dots/bspwm/sxhkdrc" "$config_dir/bspwm/sxhkdrc"
    ln -sfv "$config_dir/bspwm/bspwmrc" "$config_dir/autorandr/postswitch"  # for autorandr

    find "$dots/bspwm/scripts" -type f -executable | while read -r f; do
        ln -sfv "$f" "$bin/bspwm_$(basename -- "$f")"
    done
    desktop-file-install --dir="$HOME/.local/share/applications" "$dots/bspwm/scripts/pick_node.desktop"
    update-desktop-database "$HOME/.local/share/applications"
}

setup_dunst() {
    mkdir -pv "$config_dir/dunst"
    ln -sfv "$dots/dunst/dunstrc" "$config_dir/dunst/dunstrc"
}

setup_foot() {
    mkdir -pv "$config_dir/foot"
    ln -sfv "$dots/foot/foot.ini" "$config_dir/foot/foot.ini"
}

setup_git() {
    mkdir -pv "$config_dir/git"
    ln -sfv "$dots/git/config" "$config_dir/git/config"
}

setup_kanshi() {
    mkdir -pv "$config_dir/kanshi"
    ln -sfv "$dots/kanshi/config" "$config_dir/kanshi/config"
}

setup_logiops() {
    sudo ln -sfv "$dots/logiops/logid.cfg" "/etc/"
}

setup_mako() {
    mkdir -pv "$config_dir/mako"
    ln -sfv "$dots/mako/config" "$config_dir/mako/config"
}

setup_mpv() {
    mkdir -pv "$config_dir/mpv"
    ln -sfv "$dots/mpv/mpv.conf" "$config_dir/mpv/mpv.conf"
}

setup_picom() {
    mkdir -pv "$config_dir/picom"
    ln -sfv "$dots/picom/picom.conf" "$config_dir/picom/picom.conf"
}

setup_polybar() {
    mkdir -pv "$config_dir/polybar" "$bin"
    ln -sfv "$dots/polybar/config" "$config_dir/polybar/config"
    ln -sfv "$dots/polybar/Arthur" "$config_dir/polybar/Arthur"

    find "$dots/polybar/scripts" -type f -executable | while read -r f; do
        ln -sfv "$f" "$bin"
    done

}

setup_river() {
    mkdir -pv "$config_dir/river" "$bin"
    ln -sfv "$dots/river/init" "$config_dir/river/init"
    ln -sfv "$dots/river/wayland_init" "$bin"
}

setup_rofi() {
    mkdir -pv "$config_dir/rofi"

    for f in "$dots"/rofi/*.rasi; do
        ln -sfv "$f" "$config_dir/rofi/"
    done

    find "$dots/rofi" -type f -executable | while read -r f; do
        ln -sfv "$f" "$bin"
    done

    desktop-file-install --dir="$HOME/.local/share/applications" /usr/share/applications/spotify.desktop \
        --set-key=Exec --set-value='sh -c "wmctrl -xa spotify || spotify %U"'
    desktop-file-install --dir="$HOME/.local/share/applications" /usr/share/applications/telegramdesktop.desktop \
        --set-key=Exec --set-value='sh -c "wmctrl -xa telegram-desktop || telegram-desktop %u"'

    update-desktop-database "$HOME/.local/share/applications"
}

setup_spotifyd() {
    echo "Don't forget to (re)start the spotifyd systemd unit"
    mkdir -pv "$bin"
    ln -sfv "$dots/spotifyd/spotifyd_notification" "$bin/"

}

setup_st() {
    echo Building st probably requires internet connection
    cd "$dots/st"; makepkg -sicf; cd -
}

setup_sxhkd() {
    mkdir -pv "$config_dir/sxhkd"
    ln -sfv "$dots/sxhkd/sxhkdrc" "$config_dir/sxhkd/sxhkdrc"
}

setup_udevmon() {
    echo "Don't forget to (re)start the interception tools systemd unit"
    sudo ln -sfv "$dots/udevmon/config.yml" "/etc/interception/udevmon.d/config.yml"

}

setup_vim() {
    echo Setting up Vim requires internet connection
    mkdir -pv "$HOME/.vim" "$config_dir/nvim"
    ln -sfv "$dots/vim/vimrc" "$HOME/.vim/vimrc"
    ln -sfv "$dots/vim/init.vim" "$config_dir/nvim/init.vim"
    curl -fLo "$HOME/.vim/autoload/plug.vim" --create-dirs \
        https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
    vim +PlugInstall +qall

}

setup_x() {
    ln -sfv "$dots/x/xinitrc" "$HOME/.xinitrc"

    find "$dots/x" -type f -executable | while read -r f; do
        ln -sfv "$f" "$bin"
    done

    desktop-file-install --dir="$HOME/.local/share/applications" "$dots/x/reset_monitors.desktop"
    update-desktop-database "$HOME/.local/share/applications"
}

setup_zathura() {
    mkdir -pv "$config_dir/zathura"
    ln -sfv "$dots/zathura/zathurarc" "$config_dir/zathura/zathurarc"
}

setup_zsh() {
    ln -sfv "$dots/zsh/zprofile" "$HOME/.zprofile"
    ln -sfv "$dots/zsh/zshrc" "$HOME/.zshrc"
    ln -sfv "$dots/zsh/zshenv" "$HOME/.zshenv"
}


echo Remember to set DOTS environment variable before using

while [ "$1" ]; do
    if setup_"$1"; then
        echo "$1 has been set up"
    else
        echo "Tried to install $1 but command failed (or was unrecognised)"
    fi
    shift
done
