/*
-----------------------------------------------------------------------------
This source file is part of VPET - Virtual Production Editing Tool
http://vpet.research.animationsinstitut.de/
http://github.com/FilmakademieRnd/v-p-e-t

Copyright (c) 2016 Filmakademie Baden-Wuerttemberg, Institute of Animation

This project has been realized in the scope of the EU funded project Dreamspace
under grant agreement no 610005.
http://dreamspaceproject.eu/

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; version 2.1 of the License.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
-----------------------------------------------------------------------------
*/

#ifndef COMPANYNAMEKATANA_SCENEDISTRIBUTORINFOPLUGIN_H
#define COMPANYNAMEKATANA_SCENEDISTRIBUTORINFOPLUGIN_H

#include "PluginState.h"

#include <FnRender/plugin/RenderBase.h>

#include <string>
#include <queue>

#include <zmq.hpp>

//#include <pthread.h>


namespace Dreamspace
{
namespace Katana
{

    /**
     * \ingroup SceneDistributorPlugin
     */

    /**
     * @brief SceneDistributor Render Plugin
     */
    class SceneDistributorPlugin : public FnKat::Render::RenderBase
    {
    public:

        SceneDistributorPlugin(FnKat::FnScenegraphIterator rootIterator,
                             FnKat::GroupAttribute arguments);
        ~SceneDistributorPlugin();

        // Render Control

        int start();

        int pause();

        int resume();

        int stop();

        // Interactive live updates

        int startLiveEditing();

        int stopLiveEditing();

        int processControlCommand(const std::string& command);

        int queueDataUpdates(FnKat::GroupAttribute updateAttribute);

        int applyPendingDataUpdates();

        bool hasPendingDataUpdates() const;

        // Disk Render

        void configureDiskRenderOutputProcess(FnKat::Render::DiskRenderOutputProcess& diskRenderOutputProcess,
                                              const std::string& outputName,
                                              const std::string& outputPath,
                                              const std::string& renderMethodName,
                                              const float& frameTime) const;

        // Plugin Interface

        static Foundry::Katana::Render::RenderBase* create(FnKat::FnScenegraphIterator rootIterator, FnKat::GroupAttribute args)
        {
            return new SceneDistributorPlugin(rootIterator, args);
        }


        static void flush()
        {

        }

    private:
        SceneDistributorPluginState _sharedState;

        // Live render
        struct Update
        {
            std::string type;
            std::string location;
            FnAttribute::GroupAttribute attributesAttr;
            FnAttribute::GroupAttribute xformAttr;
        };
        typedef std::queue<Update> UpdateQueue;

        UpdateQueue _cameraUpdates;
        void updateCamera();

		//zeroMQ context

		//zeroMQ thread
		pthread_t thread;
		
	
    };
    
    static void* server(void* scene);

    /**
     * @}
     */
}
}

#endif
