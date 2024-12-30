//
// Created by Romain on 30/12/2024.
//

#ifndef INFOWINDOW_H
#define INFOWINDOW_H

class InfoWindow {
   public:
    InfoWindow();
    ~InfoWindow() = default;

    void Render();

    /* Setters */
    void SetPlayerPosition(glm::vec3 position);

    static std::shared_ptr<InfoWindow> Create();

   private:
    glm::vec3 m_PlayerPos;
};

#endif  // INFOWINDOW_H
