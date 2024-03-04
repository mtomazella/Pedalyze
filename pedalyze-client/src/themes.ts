const retro = {
  darker: '#2C0A4A',
  dark: '#6420AA',
  primary: '#FF3EA5',
  secondary: '#FF7ED4',
  light: '#FFB5DA',
}

const pastel = {
  light: '#FFE6E6',
  primary: '#E1AFD1',
  secondary: '#AD88C6',
  dark: '#7469B6',
}

const techno = {
  darker: '#0b0c10',
  dark: '#1f2833',
  primary: '#66FCF1',
  secondary: '#45A29E',
  light: '#C5C6C7',
}

const teal = {
  lighter: '#feffff',
  light: '#def2f1',
  primary: '#3aafa9',
  secondary: '#2b7a78',
  dark: '#17252a',
}

const vibrantLight = {
  lighter: '#feffff',
  light: '#def2f1',
  primary: '#FF3EA5',
  secondary: '#AD88C6',
  dark: '#17252a',
}

export const themes = {
  retro: {
    background: retro.dark,
    home: {
      titles: retro.light,
      visualization: {
        buttons: {
          border: retro.primary,
          background: retro.darker,
          emptyBackground: retro.dark,
        },
        channels: {
          border: retro.secondary,
          background: retro.darker,
          emptyBackground: retro.dark,
        },
      },
    },
  },
  pastel: {
    background: pastel.light,
    home: {
      titles: pastel.dark,
      visualization: {
        buttons: {
          border: pastel.primary,
          background: pastel.dark,
          emptyBackground: pastel.light,
        },
        channels: {
          border: pastel.secondary,
          background: pastel.dark,
          emptyBackground: pastel.light,
        },
      },
    },
  },
  techno: {
    background: techno.darker,
    home: {
      titles: techno.light,
      visualization: {
        buttons: {
          border: techno.primary,
          background: techno.dark,
          emptyBackground: techno.darker,
        },
        channels: {
          border: techno.secondary,
          background: techno.dark,
          emptyBackground: techno.darker,
        },
      },
    },
  },
  teal: {
    background: teal.lighter,
    home: {
      titles: teal.dark,
      visualization: {
        buttons: {
          border: teal.primary,
          background: teal.dark,
          emptyBackground: teal.light,
        },
        channels: {
          border: teal.secondary,
          background: teal.dark,
          emptyBackground: teal.light,
        },
      },
    },
  },
  vibrantLight: {
    background: vibrantLight.lighter,
    home: {
      titles: vibrantLight.dark,
      visualization: {
        buttons: {
          border: vibrantLight.primary,
          background: vibrantLight.dark,
          emptyBackground: vibrantLight.light,
        },
        channels: {
          border: vibrantLight.secondary,
          background: vibrantLight.dark,
          emptyBackground: vibrantLight.light,
        },
      },
      sideBar: {
        border: vibrantLight.light,
      },
    },
  },
}
